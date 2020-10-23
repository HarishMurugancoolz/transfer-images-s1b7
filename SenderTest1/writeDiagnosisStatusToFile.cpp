#include "writeDiagnosisStatusToFile.h"
using namespace std;


void WriteDiagnosisStatusOfImageToFile(int startImage, int stopImage)
{
	ofstream fout;
	fout.open("Status.csv", ios::trunc);
	if (fout.is_open())
	{
		fout << "IMAGE_NAME" << "," << "DIAGNOSIS_STATUS" << "\n";
		for (int currentImage = startImage; currentImage <= stopImage; currentImage++)
		{
			fout <<currentImage<<".img" << ","<<"PENDING" << "\n";
		}
	}
	fout.close();
}