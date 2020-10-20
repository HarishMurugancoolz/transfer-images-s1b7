#pragma warning(disable:4996)
#include "catch.hpp"
#include "SenderMainFunctions.h"
#include <iostream>

//****************************************************************************************************************************
//****************************************************************************************************************************

int main(int argc, char* argv[])
{
	SAMP_BOOLEAN            sampBool;
	STORAGE_OPTIONS         options;
	MC_STATUS               mcStatus;
	int                     applicationID = -1, associationID = -1, imageCurrent = 0;
	int                     imagesSent = 0L, totalImages = 0L, fstatus = 0;
	double                  seconds = 0.0;
	void                    *startTime = NULL, *imageStartTime = NULL;
	char                    fname[512] = { 0 };  /* Extra long, just in case */
	char   				    statusMsg[512] = { 0 };
	size_t                  totalBytesRead = 0L;
	InstanceNode            *instanceList = NULL, *node = NULL;
	FILE*                   fp = NULL;

	ReadImage* reader = new ReadImage;
	SendImage* sender = new SendImage;
	ImageList* imgList = new ImageList;

	sampBool = TestCmdLine(argc, argv, &options);
	exitApplicationIfNotNormalCompletion(sampBool == SAMP_FALSE);

	/*Library Must always be initialized first*/
	mcStatus = MC_Library_Initialization(NULL, NULL, NULL);
	exitApplicationIfNotNormalCompletion(mcStatus != MC_NORMAL_COMPLETION);

	mcStatus = MC_Register_Application(&applicationID, options.LocalAE);
	exitApplicationIfNotNormalCompletion(mcStatus != MC_NORMAL_COMPLETION);

	/*AE Registration successfull*/

	addImagesToList(&options, imgList, &instanceList);

	totalImages = imgList->GetNumNodes(instanceList);

	std::cout << "TotalIMages :" << totalImages << std::endl;

	/*open association to Storing Server*/
	openAssociation(&applicationID, &associationID, &options);


	mcStatus = MC_Get_Association_Info(associationID, &options.asscInfo);
	PrintStatus("MC_Get_Association_Info failed", mcStatus != MC_NORMAL_COMPLETION);

	printf("Connected to remote system [%s], Max operations %d\n\n", options.RemoteAE, options.asscInfo.MaxOperationsInvoked);
	fflush(stdout);

	node = instanceList;

	while (node)
	{
		sampBool = reader->read(&options, applicationID, node);
		if (!sampBool)
		{
			node->imageSent = SAMP_FALSE;
			printf("Can not open image file [%s]\n", node->fname);
			node = node->Next;
			continue;
		}

		sampBool = sender->send(&options, associationID, node);
		sprintf(statusMsg, "Failure in sending file [%s].", node->fname);
		abortAndReleaseApplicationOnFailure(statusMsg, !sampBool, &associationID, &applicationID);


		sampBool = imgList->UpdateNode(node);
		sprintf(statusMsg, "Warning, unable to update node with information [%s].", node->fname);
		abortAndReleaseApplicationOnFailure(statusMsg, !sampBool, &associationID, &applicationID);


		setNodeResponseParamsOnSucces(node, &imagesSent);


		mcStatus = MC_Free_Message(&node->msgID);
		PrintStatus("MC_Free_Message failed for request message", mcStatus != MC_NORMAL_COMPLETION);


		sampBool = ReadResponseMessages(&options, associationID, 1, &instanceList, NULL);
		sprintf(statusMsg, "Failure in reading response message, aborting association.");
		abortAndReleaseApplicationOnFailure(statusMsg, !sampBool, &associationID, &applicationID);



		node = node->Next;
	}
	/*Close Application after sending images*/
	closeAssociation(&applicationID, &associationID);



	/* Free the node list's allocated memory */
	imgList->FreeList(&instanceList);

	/*
	 * Release all memory used by the tool kit.
	 */
	PrintStatus("Error releasing the library.\n", MC_Library_Release() != MC_NORMAL_COMPLETION);


	delete reader;
	delete sender;
	delete imgList;

	return(EXIT_SUCCESS);
}


