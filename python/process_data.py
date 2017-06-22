#!/usr/bin/env/ python
# -*- coding: utf8 -*-

"""
author:zhipengliu
data:2017-06-17
define isolated gesture data preprocessing class
"""
import re
import sys, os
import pdb
import numpy as np
import subprocess
import time
import cv2
from GetSubfileName import *


class isoProcess(object):
    """define isolated gesture data preprocessing class, it can generate input and output file list"""
    def __init__(self):
        super(isoProcess, self).__init__()
        self.clipLength = 32#clip length
        self.nlabel = 249#hand gesture label
        self.width = 320# image width
        self.height = 240 # image height
    """
    cvtOriData2LabelData function: convert origitnal isolated gesture train file to new file based on label in order to use it more conveniently
    @filepath: the path of training or validation file of isolated file
    @labellist: the path of training or validation label list file
    @newfile: the new labeled data file path
    @isRGB: 1 means  using rgb list, 2 means using depth list
    @usHandLabel: 1: conver hand detecion result label, 2: convert video data
    """
    def cvtOriData2LabelData(self, filepath = None, labellist = None, newfile = None, isRGB = 1, isHandLabel = 1):
        timestart = time.time()
        if not os.path.exists(labellist):
            print("please set the correct path to labellist")
            sys.exit()
        if not os.path.exists(newfile):
            strcmd = "mkdir -p " + newfile
            subprocess.call(strcmd, shell = True)

        liststream = open(labellist, 'r')
        allLines = liststream.readlines()
        r = re.compile('[ \t\n\r:]+')
        r1 = re.compile('/')       
        cnt = 0

        for line in allLines:
            print("%d/%d" % (cnt, len(allLines)))
            cnt = cnt + 1
            splitLine = r.split(line)
            ##splitLine: RGB path, depth path, label
            label = splitLine[2]
            labelPath = newfile + "/%03d" % (int(label))
            if not os.path.exists(labelPath):
                os.mkdir(labelPath)
            #RGB, hand detecion label
            if isRGB == 1 and isHandLabel == 1:
                split_again = r1.split(splitLine[0])
                oriFilePath = filepath + "/" + split_again[0] + "/" + split_again[1] + "/Label_" + split_again[2][: -4] + ".txt"
            #RGB, video
            elif isRGB == 1 and isHandLabel == 2:
                oriFilePath = filepath + "/" + splitLine[0]
            #depth, hand detecion label
            elif isRGB == 2 and isHandLabel == 1:
                split_again = r1.split(splitLine[1])
                oriFilePath = filepath + "/" + split_again[0] + "/" + split_again[1] + "/Label_" + split_again[2][: -4] + ".txt"
            #depth, video
            else:
                oriFilePath = filepath + "/" + splitLine[1]
            strCPcmd = "cp -r " + oriFilePath + " " + labelPath
            subprocess.call(strCPcmd, shell = True)
        timeend = time.time()
        print "cvtOriData2LabelData using time = " + str(timeend - timestart)

    """
    convert video to image
    required: ffmpeg
    @pathVideo: path to video
    @pathImageJpg: path to new generated image file
    @isRGB: 1: RGB, 2: depth
    """
    def cvtVideo2Img(self, pathVideo = None, pathImageJpg = None, isRGB = 1):
        timestart = time.time()
        subRGB = GetSubfileName(pathVideo)
        if not os.path.exists(pathImageJpg):
            strcmd = "mkdir -p " + pathImageJpg
            subprocess.call(strcmd, shell = True)
        nSubfile = len(subRGB)
        for i in range(0, nSubfile):
            subfileName = subRGB[i]
            print "---------------" + subfileName + "----------------"
            subRGBfilePath = pathVideo + "/" + subfileName
            oneLabelImagePath = pathImageJpg + "/" + subfileName
            if os.path.exists(oneLabelImagePath) == False:
                os.mkdir(oneLabelImagePath)
            subsubfile = GetSubfileName(subRGBfilePath)
            nSentence = len(subsubfile)
            for j in range(nSentence):
                videostr = subsubfile[j]
                if isRGB == 1:
                    if videostr[0] == 'K':
                        continue
                else:  
                    if videostr[0] == 'M':
                        continue
                oneMefile = subRGBfilePath + "/" + videostr
                print "sentence: "  + videostr
                oneMeSaveFile = oneLabelImagePath + "/" + videostr[ 0 :  -4]
                if os.path.exists(oneMeSaveFile) == False:
                    os.mkdir(oneMeSaveFile)

                strcmd = "ffmpeg -i " + oneMefile + " -r 10 -f image2 " + oneMeSaveFile + "/%06d.jpg"
                subprocess.call(strcmd, shell=True)
                timeend = time.time()
            print "time = " + str(timeend - timestart)
    """
    get hand region in the whole image and black the remaining region
    @oriImgFile: path to origial image
    @detectionFile: path to hand detecion result arranged as hand label
    @saveFile: the saved new path
    """
    def blackNonHand(self, oriImgFile = None, detectionFile = None, saveFile = None ):
        width = self.width
        height = self.height
        if not os.path.exists(saveFile):
            strcmd = "mkdir -p " + saveFile
            subprocess.call(strcmd, shell = True)
        labelNameSets = GetSubfileName(oriImgFile)
        start = time.time()
        r = re.compile(" ")
        cnt_w = 0
        for labelName in labelNameSets:
            saveLabelFile = saveFile + "/" + labelName
            if not os.path.exists(saveLabelFile):
                os.mkdir(saveLabelFile)
            deLabelFile = detectionFile + "/" + labelName
            imgLabelFile = oriImgFile + "/" + labelName
            videoNameSets = GetSubfileName(imgLabelFile)
            devideoNameSets = GetSubfileName(deLabelFile)
            numVideo = len(videoNameSets)
            for i in range(numVideo):
                saveVideoPath = saveLabelFile + "/" + videoNameSets[i]
                print(labelName, videoNameSets[i])
                if not os.path.exists(saveVideoPath):
                    os.mkdir(saveVideoPath)
                elif len(GetSubfileName(saveVideoPath)) != 0:
                    continue

                imgVideoPath = imgLabelFile + "/" + videoNameSets[i]
                deVideoPath = deLabelFile + "/" + devideoNameSets[i]
                imgNameSets = GetSubfileName(imgVideoPath)
                nimgs = len(imgNameSets)
                detecionHand = np.zeros((nimgs, 9)) #frame id + detecion result
                if not os.path.exists(deVideoPath):
                    print deVideoPath + "dose not exist!"
                    continue
                print(deVideoPath)
                stream = open(deVideoPath, 'r')
                lines = stream.readlines()
                for oneline in lines:
                    oneline = oneline[: -1]
                    split = r.split(oneline)                
                    frameId = int(split[0]) #begin from 0
                    # print("frame:", frameId)
                    if frameId >= nimgs:
                        break
                    detecionHand[frameId, 0] = frameId
                    for j in range(len(split) - 1):
                        detecionHand[frameId, j + 1] = int(split[j + 1])
                cnt = 0
                for j in range(nimgs):
                    if detecionHand[j, 1] == 0:
                        continue
                    imgPath = imgVideoPath + "/" + imgNameSets[j]
                    saveImgPath = saveVideoPath + "/%06d.jpg" % (cnt)
                    cnt = cnt + 1
                    imgContent = cv2.imread(imgPath)
                    mask = np.zeros((height, width, 3))
                    detecionHand = detecionHand.astype(np.int64)
                    hand1 = detecionHand[j, 1 : 5] # (x1,y1, x2, y2)
                    hand2 = detecionHand[j, 5 :]
                    if hand1[0] != 0:
                        for row in range(hand1[0], hand1[2]):
                            for col in range(hand1[1], hand1[3]):
                                mask[col, row, :] = 1
                    if hand2[0] != 0:
                        for row in range(hand2[0], hand2[2]):
                            for col in range(hand2[1], hand2[3]):
                                mask[col, row, :] = 1
                    handImg = imgContent * mask
                    # pdb.set_trace()
                    cv2.imwrite(saveImgPath, handImg)
                    # pdb.set_trace()
                end = time.time()
                print("using time:", end - start)
    """
    read isolated face detection file
    @filepath: path to isolated face detection file
    """            
    def readFaceFileIso(self, filepath = None):
        if os.path.exists(filepath) == False:
            print "isolated face file: " + filepath + "dose not exists!"
            return 0, 0, 0
        filestream = open(filepath)
        content = np.loadtxt(filestream)
        idVideo = content[:, 0]
        allfaceX = (content[:, 2] + content[:, 4]) / 2
        allfaceY = (content[:, 3] + content[:, 5]) / 2
        print "content.shape", content.shape
        return idVideo, allfaceX, allfaceY
    """
    get hand and face (20x20 gray) region in the whole image and black the remaining region
    @oriImgFile: path to only hand image image
    @faceDetecionPath: path to isolated face detecion file
    @saveFile: the saved new path
    """
    def blackNonHandFace(self, oriImgFile = None, faceDetecionPath = None, saveFile = None ):
        width = self.width
        height = self.height
        if not os.path.exists(saveFile):
            strcmd = "mkdir -p " + saveFile
            subprocess.call(strcmd, shell = True)
        labelNameSets = GetSubfileName(oriImgFile)
        start = time.time()
        idVideo, allfaceX, allfaceY = self.readFaceFileIso(filepath = faceDetecionPath)
        dic_id2line = {}
        numVideo = idVideo.shape[0]
        for i in range(numVideo):
            dic_id2line[idVideo[i]] = i

        for labelName in labelNameSets:
            saveLabelFile = saveFile + "/" + labelName
            if not os.path.exists(saveLabelFile):
                os.mkdir(saveLabelFile)

            imgLabelFile = oriImgFile + "/" + labelName
            videoNameSets = GetSubfileName(imgLabelFile)
            numVideo = len(videoNameSets)
            for i in range(numVideo):
                saveVideoPath = saveLabelFile + "/" + videoNameSets[i]
                print(labelName, videoNameSets[i])

                OneVideoId = int(videoNameSets[i][2:])
                if dic_id2line.has_key(OneVideoId):
                    faceCX = allfaceX[dic_id2line[OneVideoId]]
                    faceCY = allfaceY[dic_id2line[OneVideoId]]
                    faceSize = 10
                    facex1 = max(0, faceCX - faceSize)
                    facey1 = max(0, faceCY - faceSize)
                    facex2 = min(width, faceCX + faceSize)
                    facey2 = min(height, faceCY + faceSize)
                    faceRect = (facex1, facey1, facex2, facey2)
                else:#if there is not face detection result
                    faceCX = width / 2
                    faceCY = height / 2
                    faceRect = (faceCX - faceSize, faceCY - faceSize, faceCX + faceSize, faceCY + faceSize)
                if not os.path.exists(saveVideoPath):
                    os.mkdir(saveVideoPath)
                else:
                    continue
                imgVideoPath = imgLabelFile + "/" + videoNameSets[i]
                imgNameSets = GetSubfileName(imgVideoPath)
                nimgs = len(imgNameSets)
                for j in range(nimgs):
                    imgPath = imgVideoPath + "/" + imgNameSets[j]
                    saveImgPath = saveVideoPath + "/" + imgNameSets[j]
                    imgContent = cv2.imread(imgPath)

                    for row in range(int(faceRect[0]), int(faceRect[2])):
                        for col in range(int(faceRect[1]), int(faceRect[3])):
                            if(imgContent[col, row, 1] <= 10):
                                imgContent[col, row, :] = 123
                    # pdb.set_trace()
                    cv2.imwrite(saveImgPath, imgContent)
                    # pdb.set_trace()
                end = time.time()
                print("using time:", end - start)
    """
    generate input image list file for c3d 
    @pathImageJpg: path to prepared image image
    @inputfilename: input image list file for c3d
    """
    def set_image_list(self, pathImageJpg = None, inputfilename = None):
        nlabel = self.nlabel
        clipLength = self.clipLength
        timestart = time.time()
        subRGB = GetSubfileName(pathImageJpg)
        featureCount = 0
        inputfilestream = open(inputfilename, 'w+')
        cnt = 0
        for i in range(nlabel):
            subfileName = subRGB[i]
            print "---------------" + subfileName + "----------------"
            subRGBfilePath = pathImageJpg + "/" + subfileName
            DTlRGBfileName = GetSubfileName(subRGBfilePath)
            labelVideoSize = len(DTlRGBfileName)

            for j in range(labelVideoSize):
                videostr = DTlRGBfileName[j]
                # if videostr[0] == 'h':
                #     continue
                #print "nvideo = " + videostr
                oneVideoPath = subRGBfilePath + "/" + videostr

                imagelist = GetSubfileName(oneVideoPath)
                nframe = len(imagelist)
                if nframe != 32:
                    print("wrong:", oneVideoPath)
                for k in range(1, nframe + 1, clipLength):
                    if k + clipLength  - 1 > nframe:
                        break
                    frameStart = k
                    cnt = cnt + 1
                    print(cnt)
                    inputsetting = oneVideoPath + "/ " + str(frameStart) + " " + str(i) + "\n"
                    inputfilestream.writelines(inputsetting)
        inputfilestream.close() 
    """
    generate output image list file for c3d 
    @pathImageJpg: path to prepared image image
    @pathC3Dfeature: the generate c3d fc6 feature file
    @outputfilename: output image list file for c3d
    """
    def set_c3d_output_list(self, pathImageJpg = None, pathC3Dfeature = None, outputfilename = None):
        nlabel = self.nlabel
        clipLength = self.clipLength
        timestart = time.time()
        if not os.path.exists(pathC3Dfeature):
            strcmd = "mkdir -p " + pathC3Dfeature
            subprocess.call(strcmd, shell = True)

        subRGB = GetSubfileName(pathImageJpg)
        outputfilestream = open(outputfilename, 'w+')
        cnt = 0
        for i in range(nlabel):
            subfileName = subRGB[i]
            print(subfileName)
            #print "---------------" + subfileName + "----------------"
            subRGBfilePath = pathImageJpg + "/" + subfileName
            outputLabelfile = pathC3Dfeature + "/" + subfileName
            if not os.path.exists(outputLabelfile):
                os.mkdir(outputLabelfile)
            DTlRGBfileName = GetSubfileName(subRGBfilePath)
            labelVideoSize = len(DTlRGBfileName)

            for j in range(labelVideoSize):
                videostr = DTlRGBfileName[j]
                # if videostr[0] == 'h':
                #    continue
                oneVideoPath = subRGBfilePath + "/" + videostr
                outputVideoPath = outputLabelfile + "/" + videostr
                if not os.path.exists(outputVideoPath):
                    os.mkdir(outputVideoPath)
                else:
                    continue
                imagelist = GetSubfileName(oneVideoPath)
                nframe = len(imagelist)
                for k in range(1, nframe + 1, clipLength):
                    if k + clipLength  - 1 > nframe:
                        break
                    frameStart = k
                    cnt = cnt + 1
                    # print(cnt)
                    outputsetting =   "%s/%06d\n" % (outputVideoPath, frameStart)
                    outputfilestream.writelines(outputsetting)
        outputfilestream.close()
    """
    unify the video frame to constant frams by sampling
    @filepath: the path to original image file
    @savepath: unified image saved file
    """
    def frameUnification(self, filepath = None, savepath = None):
        uniFrames = self.clipLength
        if not os.path.exists(savepath):
            strcmd = "mkdir -p " + savepath
            subprocess.call(strcmd, shell = True)
        subLabelName = GetSubfileName(filepath)
        cnt_w = 0
        for labeName in subLabelName:
            print(labeName)
            subSaveLabelfile = savepath + "/" + labeName
            if not os.path.exists(subSaveLabelfile):
                os.mkdir(subSaveLabelfile)
            subLabelPath = filepath + "/" + labeName
            sub2Names = GetSubfileName(subLabelPath)
            for sub2Name in sub2Names:
                print("----", sub2Name, "------")
                # pdb.set_trace()
                saveVideoPath = subSaveLabelfile + "/" + sub2Name
                if not os.path.exists(saveVideoPath):
                    os.mkdir(saveVideoPath)
                elif len(GetSubfileName(saveVideoPath)) != 0:
                    continue
                cnt_w = cnt_w + 1
                videoPath = subLabelPath + "/" + sub2Name
                AllImageNames = GetSubfileName(videoPath)
                oriframe = len(AllImageNames)
                rate = float(oriframe) / float(uniFrames)
                for i in range(uniFrames):
                    oriID = int(i * rate)
                    oriID = oriID if oriID < oriframe else oriframe - 1
                    #print("oriID:", oriID)
                    #print("i:",i)
                    oriimagePath = videoPath + "/" + "%06d.jpg" % (oriID)
                    oridetPath = saveVideoPath + "/" + "%06d.jpg" % (oriID)
                    #print("oriImg:", oriimagePath)
                    detimagePath = saveVideoPath + "/" + "%07d.jpg" % (i + 1)
                    strCPcmd = "cp " + oriimagePath + " " + saveVideoPath
                    strMVcmd = "mv " + oridetPath + " " + detimagePath
                    subprocess.call(strCPcmd, shell = True)
                    subprocess.call(strMVcmd, shell = True)
                for i in range(uniFrames):
                    oriname = saveVideoPath + "/" + "%07d.jpg" % (i + 1)
                    destname = saveVideoPath + "/" + "%06d.jpg" % (i + 1)
                    strMVcmd = "mv " + oriname + " " + destname
                    subprocess.call(strMVcmd, shell = True)
                # pdb.set_trace()
        print(cnt_w)
if __name__ == '__main__':
    #-----------------------------------------set file path----------------------------------------------#
    oriVideoPath = "/media/zhipengliu/zhipeng_NHCI/ChaLearn2017/Iso/dataset/IsoGD_Phase_1/IsoGD_phase_1"
    labellist = "/media/zhipengliu/zhipeng_NHCI/ChaLearn2017/Iso/dataset/IsoGD_phase_2/valid_list_with_label.txt"
    labeVideofile = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/label_valid"
    timestart = time.time()
    #--------------------------------------------------------------------------------------------------------#
    ##convert origianl video to labeled video
    ##RGB video
    preprocess = isoProcess()

    preprocess.cvtOriData2LabelData(filepath = oriVideoPath, labellist = labellist, newfile = labeVideofile, isRGB = 1, isHandLabel = 2)
    ##deoth video
    preprocess.cvtOriData2LabelData(filepath = oriVideoPath, labellist = labellist, newfile = labeVideofile, isRGB = 2, isHandLabel = 2)

    ##convert original hand detecion to labeld file
    handDetectionFile = "/home/zhipengliu/liuzhuang/vgg16/DetectionLabel/iso"
    labelHDfile = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/label_valid_handDetecion"
    #RGB
    preprocess.cvtOriData2LabelData(filepath = handDetectionFile, labellist = labellist, newfile = labelHDfile, isRGB = 1, isHandLabel = 1)
    ##
    timeend = time.time()
    print("cvtOriData2LabelData is done, using time: %d minutes", (timeend - timestart) / 60.0)

    #--------------------------------------------------------------------------------------------------------#
    ##convert labeld video to image
    oriRGBImgFile = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/original_image/RGB"
    oriDepthImgFile = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/original_image/depth"
    ##RGB 
    preprocess.cvtVideo2Img(pathVideo = labeVideofile, pathImageJpg = oriRGBImgFile, isRGB = 1)
    preprocess.cvtVideo2Img(pathVideo = labeVideofile, pathImageJpg = oriDepthImgFile, isRGB = 2)
    timeend = time.time()
    print("cvtVideo2Img is done, using time: %d minutes", (timeend - timestart) / 60.0)
    #--------------------------------------------------------------------------------------------------------#

    ##get croped hand region
    #RGB, and you can set corresponding depth file and get  only_have_hand depth image and c3d input and output list file 
    only_hand_file = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/only_hand"
    preprocess.blackNonHand(oriImgFile = oriRGBImgFile, detectionFile = labelHDfile, saveFile = only_hand_file)
    timeend = time.time()
    #depth

    print("blackNonHand is done, using time: %d minutes", (timeend - timestart) / 60.0)
    #--------------------------------------------------------------------------------------------------------#
    ##unify image to 32 frame
    unifi_only_hand_file = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/unifi_32"
    preprocess.frameUnification(filepath = only_hand_file, savepath = unifi_only_hand_file)
    timeend = time.time()
    print("frameUnification is done, using time: %d minutes", (timeend - timestart) / 60.0)
    #--------------------------------------------------------------------------------------------------------#
    ##get only hand and face
    faceDetecionPath = "/home/zhipengliu/project/ChaLearn2016/IsofacePosition/IsoRGBvalidFaceDetect.txt"
    only_hand_face_file = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/only_hand_face"
    preprocess.blackNonHandFace(oriImgFile = unifi_only_hand_file, faceDetecionPath = faceDetecionPath, saveFile = only_hand_face_file)
    timeend = time.time()
    print("blackNonHandFace is done, using time: %d minutes", (timeend - timestart) / 60.0)
    #--------------------------------------------------------------------------------------------------------#
    ##set input list file for c3d
    inputlist = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/unifi_32/valid_input_list.txt"
    preprocess.set_image_list(pathImageJpg = only_hand_face_file, inputfilename = inputlist)

    ##set output list file for c3d
    outputlist = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/list/output/valid_output_list.txt"
    pathfeature = "/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/test/feature_valid"
    preprocess.set_c3d_output_list(pathImageJpg = only_hand_face_file, pathC3Dfeature = pathfeature, outputfilename = outputlist)
    timeend = time.time()
    print("preprocessing isolated data is done, using time: %d minutes", (timeend - timestart) / 60.0)