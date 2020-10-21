#pragma once
#include "../sender/util_structures.h"
#include "../sender/general_util.h"
#include "../sender/ReadMessageFromFile.h"
#include "../sender/SendImage.h"
#include "../sender/ImageList.h"
#include "../sender/ReadImage.h"
void openAssociation(int* A_applicationID, int* A_associationID, STORAGE_OPTIONS* A_options);
void exitApplicationIfNotNormalCompletion(bool statusBool);
void addImagesToList(STORAGE_OPTIONS* options, ImageList* imgList, InstanceNode** node);
void setNodeResponseParamsOnSucces(InstanceNode* node, int* imgSent);
void abortAndReleaseApplicationOnFailure(char* statusMsg, bool statusBool, int* associationID, int* applicationID);
void closeAssociation(int* A_pplication, int* A_associationID);

