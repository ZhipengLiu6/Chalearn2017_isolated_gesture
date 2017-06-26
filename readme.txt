This an implementaion of our method about ChaLearn LAP Large-scale Isolated Gesture Recognition Challenge (Round 2) @ICCV 2017

## Notes: This code was tested on Windows10 OS with VS2012 and Ubuntu 14.04 OS with Python 2.7, caffe-C3D, Sklearn, faster-rcnn.
Please double check the paths in code before your run it.

###Training:

##Step1: Get face and hand detetion about training dataset.
Face and hand postion can be detected by using the codes in the detection folder. To use these codes, you can refer to Detection-Pipeline-Iso.pdf. 
Finally, you can get all the detection results. (We have also uploaded it in github. The hand detecion results are saved in python/data/handDetection, The face detecion results are saved in python/data/IsofacePosition). The phase will take about 3 days in a TiTan X GPU. 

## Step2: Preprocess the training dataset and get the input data and setting files needed by Setp3(for c3d finetune). 
Dependencies: cv2, numpy, ffmpeg. 

All needed  data are lied in python/data.  The directory should have:

handDetection
IsofacePosition
IsoGD_phase_1_RGB/train
IsoGD_phase_1_aligned_depth/train
IsoGD_phase_2_aligned_depth/test
IsoGD_phase_2_RGB/test
test_list.txt
train_list.txt
train_list_one_level.txt
valid_list.txt

You should place all 180 training RGB  and aligned depth  files in IsoGD_phase_1_RGB/train and IsoGD_phase_1_aligned_depth/train respectively and place  all 32 testing RGB and aligned depth files in IsoGD_phase_2_aligned_depth/test and IsoGD_phase_2_RGB/test. 

train_list_one_level.txt is a modified train_list.txt. It only contains 200 relative paths of video.  We take it as a example to shou you  how to get the input data and setting files needed by Setp3 quickly. You can replace  train_list_one_level.txt with  train_list.txt in preprocessTrainDepthData.sh and preprocessTrainRGBData.sh to get all needed files.

You can run the following commands to get all the files:

sh preprocessTrainRGBData.sh  #(for getting the 'RGB files' needed by finetuning c3d of traning set)
sh preprocessTrainDepthData.sh  #(for getting the 'depth files' needed by finetuning c3d of traning set)

Then, the  generated input data for c3d will be saved in python/data/train/unifi_only_hand_file/depth and  and  python/data/train/only_hand_face_file/rgb. The setting files will be saved in python/train_list_c3d. Since we finetune the c3d with RGB and depth respectively, the data and setting files will contain both RGB and depth files.  For more about the input data and the setting files, you can refer to C3D User Guide(https://docs.google.com/document/d/1-QqZ3JHd76JfimY4QKqOojcEaf5g3JS0lNh-FHTxLag/edit).



The two scripts includes several steps as follows: 

### Step2.1: Change the organization of the training dataset. You can see the results in python/data/train/labelDepthVideo/001. Each folder contains the videos with the same label. (For example, '001' means all the videos labeled 1).

### Step2.2: Convert original  RGB and depth video to images.

### Step2.3: Get the images containing only hands in RGB and Depth.

### Step2.4: Depth and RGB frames unification.

### Step2.4: Get the images containing only hands and face in RGB.

### Step2.5: Get the setting files for finetuning the C3D model, which is pre-trained on Sports-1M (The pre-trained model can be downloaded from https://drive.google.com/file/d/0Bx-2rTokRAt1Vm9nLWItQTgtSVE/view).

Tips: Final RGB images only have face and hands. Final depth images only have hands. The length of C3D input videos are all 32 frames by sampling. (All functions have detail comments in python/process_data.py)

##Step3: Finetune the C3D with final RGB images and depth image respectively. The training process stops after 100000 iterations. It will cost about 60 hours in a Titan X GPU for finetuning the C3D.

###Step3.1: Installation. For more information about the installation and usage, please refer ro http://vlg.cs.dartmouth.edu/c3d/. After Installation of C3D, place C3D-v1.0-key-parts/c3d_finetuning_len_32_only_hand_depth_map_2stream, c3d_finetuning_len_32_only_hand_face_rgb_2streams, c3d_train_ucf101 and c3d_feature_extraction in C3D-v1.0/example.

###Step3.2: Compute volume mean from input setting list. 

###Step3.3: Finetune C3D. (The finetuned c3d model can be downloaded from https://pan.baidu.com/s/1pKITNeV)

##Step4: Extracte c3d fc6 feature.

You will find python/feature has c3d  extracted feature. (The extracted c3d feature can be downloaded from https://pan.baidu.com/s/1nuPJ3uh).

Tips: the detail introduction of  Step3 and Step4 can be refered to  C3D User Guide.  You can also refer to our prototxt files inC3D-v1.0-key-parts/c3d_finetuning_len_32_only_hand_depth_map_2stream, c3d_finetuning_len_32_only_hand_face_rgb_2streams, c3d_train_ucf101.

##Step5: Read and fuse extracted feature.

Read extracted c3d feature by running read_and_fuse_feature_ubuntu_matlab/main.m. The final fused training features lie in the current directory. (the final feature can also be downloaded from https://pan.baidu.com/s/1pLrzEtl)

##Step6: To train linear-SVM model using the code of svm_c3d.py.(The svm_model file has trained svm model):

python svm_c3d.py --isTrain 1 --isTest 0


The process of testing:

##Step1: Get face and hand detecion about validation or testing dataset.

##Step2: To preprocess the training dataset and get the input data and setting files for extacting c3d fc6 feature.

sh preprocessTestRGBData.sh 
sh preprocessTestDepthData.sh  

##Step3: Extracte c3d fc6 feature like training Step4.

##Step4: Read and fuse extracted feature by running  read_and_fuse_feature_ubuntu_matlab/mainTest.m

##Step5: To test the validation or testing dataset in svm_c3d.py and get prediction file in python/submission:

python svm_c3d.py --isTrain 0 --isTest 1
