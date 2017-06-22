This an implementaion of our method about ChaLearn LAP Large-scale Isolated Gesture Recognition Challenge (Round 2) @ICCV 2017

## Notes: This code was tested on Windows10 OS with VS2012 and Ubuntu 14.04 OS with Python 2.7, caffe-C3D, sklearn, faster-rcnn.
Please double check the paths in code before your run it.
The process of training:

##Step1: Get face and hand detetion about training dataset.
Face and hand postion can be detected by using the code in the detection file. The detailed introduction can be seen in Detection-Pipeline-Iso.pdf. 
	you can get detection result, such as IsoRGBTrainFaceDetect.txt and IsoTrainHandDetection.

##Step2: Preprocess the training dataset and get special images. RGB images only have face and hand. Depth images only have hand. The length of C3D input videos are all 32 frames
by sampling.(All functions have detailed comment in process_data.py)

###Step2.1: Change the file organization as the way of label.

oriVideoPath: the original path of training dataset.
labellist: the given train video list path.
labeVideofile: the saved file path.
handDetectionFile: the hand detecion results path got from Step1 
labelHDfile: the new labeled hand detecion file path
###Step2.2: Convert RGB and depth video to images by running the funtion of cvtVideo2Img and set corresponding paths.

###Step2.3: Get the images containing only hands in RGB and Depth by running the funtion of blackNonHand and set corresponding paths.

###Step2.4: Depth and RGB frames unification and get the images containing only hands and face in RGB by running the funtion of frameUnification and blackNonHandFace.

###Step2.5: Get the input and output image list for finetuning the C3D, which is pre-trained on Sports-1M, by the function of set_image_list and set_c3d_output_list.

##Step3: Finetune the C3D with only-hand-face RGB images and only-hand Depth image respectively.

###Step3.1: Installation. For more information about the installation and usage, please refer ro http://vlg.cs.dartmouth.edu/c3d/

###Step3.2: Get mean-value file. 

###Step3.3: Finetune C3D.  c3d_finetuning_len_32_only_hand_depth_map_2stream and c3d_finetuning_len_32_only_hand_face_rgb_2streams can be placed in the directory of example. Set corresponding paths(must be careful). (The finetuned c3d model can be downloaded from https://pan.baidu.com/s/1pKITNeV)

###Step3.4: Feature extraction. C3d_feature_extraction can be placed in the directory of example. Set corresponding paths(must be careful). (The extracted c3d feature can be downloaded from https://pan.baidu.com/s/1nuPJ3uh)

###Step3.5: Read extracted c3d feature using the code of read_and_fuse_feature_ubuntu_matlab. (the final feature can also be downloaded from https://pan.baidu.com/s/1pLrzEtl)

##Step4: Train linear-SVM model using the code of svm_c3d.py.(The svm_model file has trained svm model)

The process of testing:

##Step1: Get face and hand detecion about validation or testing dataset.

##Step2: Preprocess the validation or testing dataset dataset like training.

##Step3: Feature extraction and read it like training.

##Step4: Test the validation or testing dataset in svm_c3d.py and get prediction file.
