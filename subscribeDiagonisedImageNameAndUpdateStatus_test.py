import subscribeDiagonisedImageNameAndUpdateStatus as receiver
import unittest

class subscribeTest(unittest.TestCase):
    
    def test_When_Image_name_is_given_then_open_and_update_the_status_of_image_in_file(self):
        testsamplefilename = 'temp-samples-test.csv'
        with open(testsamplefilename, 'w') as samplefile:
            samplefile.write("""IMAGE_NAME,DIAGNOSIS_STATUS
                                0.img,pending
                                1.img,pending""")
            SampleDiagnosedImageName="0.img"
            receiver.OpenAndUpdateCSVFile(SampleDiagnosedImageName, testsamplefilename)
        with open(testsamplefilename, 'r') as samplefile:
            csvFileDict=receiver.csv.DictReader(samplefile)
            for row in csvFileDict:
                self.assertTrue(row['DIAGNOSIS_STATUS'],"completed")
                break
    def test_when_the_function_getFilePath_called_then_return_the_file_path(self):
        filePath=receiver.getFilePath()
        expectedFilePath=r"C:\Users\ASUS\source\repos\TransferMedicalImages\TransferMedicalImages\Status.csv"
        self.assertTrue(filePath,expectedFilePath)

if __name__ == '__main__':
    unittest.main()
