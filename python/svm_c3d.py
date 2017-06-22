#!/usr/bin/env python
# -*- coding: utf8 -*-
import scipy.io as scio
import os, sys
import pdb
import numpy as np
import time
# from svmutil import *
# from svm import *
from sklearn import svm, datasets
from sklearn.externals import joblib
import matplotlib.pyplot as plt
import h5py
import pickle
import pprint
import re
"""
function: test the svm model, generate and save the accuracy
@x: feature, numpy, shape: (nsamples, nfeature)
@y: label, numpy, shape: (nsample): groundtruth
@modelPath: the saved linear model path
@saveResultPath: the pickle path, which is used to save the accuracy, prediction and  groundtruth result
@para: the trained parameter
"""
def test_has_gr(x = None, y = None, modelPath = None, saveResultPath = None, para = None):
    yg = y.squeeze()
    lin_svc = joblib.load(modelPath)
    predict = lin_svc.predict(x)
    cnt_correct = 0
    cnt_all = yg.shape[0]
    for i in range(cnt_all):
        if yg[i] == predict[i]:
            # print("i = %d, ground = %d, predict = %d" % (i, yg[i], predict[i]))
            cnt_correct = cnt_correct + 1

    acc = float(cnt_correct) / cnt_all
    
    print('accuracy: ', acc)
    # pdb.set_trace()
    result = {1 : acc,
                    2 : predict,
                    3 : yg,
                    4 : para,
    }
    pdb.set_trace()
    saveStream = open(saveResultPath, 'wb')
    pickle.dump(result, saveStream)
    saveStream.close()
    return predict
"""
function: test the svm model, generate prediction result
@x: feature, numpy, shape: (nsamples, nfeature)
@modelPath: the saved linear model path
@saveResultPath: the pickle path, which is used to save the prediction.
@para: the trained parameter
"""
def test_no_gr(x = None, modelPath = None, saveResultPath = None, para = None):
    lin_svc = joblib.load(modelPath)
    predict = lin_svc.predict(x)
    result = {2 : predict,
                    4 : para,
    }
    pdb.set_trace()
    saveStream = open(saveResultPath, 'wb')
    pickle.dump(result, saveStream)
    saveStream.close()
    return predict
"""
function: train and save the linear svm model
@x: feature, numpy, shape: (nsamples, nfeature)
@y: label, numpy, shape: (nsample)
@para: svm hyper-parameter
@return: none
"""
def train(x = None, y = None, saveModelPath = 'iso_training_plinear_svm_model_max_iter_2w.m', para = None):
    # pdb.set_trace()
    y = y.squeeze()
    ## set hyper-parameter
    print("begin training")
    C = para['C']
    dual = para['dual']
    class_weight = para['class_weight']
    max_iter = para['max_iter']

    lin_svc = svm.LinearSVC(C = C, dual = dual, class_weight = class_weight).fit(x, y)
    # pdb.set_trace()
    joblib.dump(lin_svc, saveModelPath)
    print("training done!")
"""
function: generate submission prediction file as the format of https://competitions.codalab.org/competitions/16491#learn_the_details-evaluation
@videoid: the id of predicted video: (1, nsample)
@predict: prediction result
@mysubfile: the file of submission
@GivenVideolistfile: the official given test video list file
@isTest: 1 : generate validation submission file; 2 : generate testing submission file 
"""
def Generate_submission_file(videoid = None,  predict = None, mysubfile = None, GivenVideolistfile = None, isTest = 1):
    videoid = videoid.squeeze()
    r = re.compile('[ \t\n\r:,/]+')
    result_class = predict
    NumAviVideo = videoid.shape[0]
    resultvideoDic = {-1: -1}           #videoid to result lineid
    for i in range(NumAviVideo):
        onevideoId = videoid[i]
        resultvideoDic[onevideoId] = i

    test_stream = open(GivenVideolistfile, 'r')
    testAllline = test_stream.readlines()
    test_stream.close()

    substream = open(mysubfile, 'w')
    numlen = len(testAllline)
    for i in range(numlen):
        oritestline = testAllline[i]
        if isTest == 2:
            onevideoId = int(oritestline[11: 16])
        elif isTest == 1:
            onevideoId = int(oritestline[12: 17])
        else:
            print("The parameter isTest is wrong!!")
            sys.exit()
        linelen = len(oritestline)
        if resultvideoDic.has_key(onevideoId):
            lineid = resultvideoDic[onevideoId]
            lable = int(result_class[lineid]) + 1
        else:
            lable = 1
        newtestline = oritestline[0 : linelen-1] + " " + str(lable) + "\n"
        substream.write(newtestline)
    substream.close()
if __name__ == '__main__':
    ##set data path
    strpara = "_iso_depth_map_only_hand_rgb_only_hand_face_2streams_iter_1k_c_Efu1"
    print("experiment type:", strpara)
    trainfilepath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/fusion/new_iso_training_fusion_depth_map_only_hand_rgb_only_hand_face_2stream.mat'
    testfilepath = '/home/zhipengliu/ChaLearn2017/IsoGesture/feature/process/fusion/new_iso_validation_fusion_depth_map_only_hand_rgb_only_hand_face_2stream.mat'
    # saveModelPath = '/home/zhipengliu/ChaLearn2017/related_work/SVM_classification/python/v1/model/iso_training_linear_svm_model' + strpara + '.m'
    saveModelPath = '/home/zhipengliu/ChaLearn2017/IsoGesture/iso_final_code/svm_model/iso_training_linear_svm_model_depth_map_only_hand_rgb_only_hand_face_2streams_iter_1k_c_Efu1.m'
    saveResultPath = '/home/zhipengliu/ChaLearn2017/related_work/SVM_classification/python/v1/result/con_validation' + strpara + '.pkl'
    submissionFile = "/home/zhipengliu/ChaLearn2017/IsoGesture/submission/valid_prediction.txt"
    GivenVideolistfile = "/home/zhipengliu/ChaLearn2017/IsoGesture/submission/valid_list.txt"
    isTrain = 0
    isTest = 1
    ## set hyper-parameter
    para = {}
    para['C'] = 0.1
    para['dual'] = False #dual=False when n_samples > n_features.
    para['class_weight'] = 'balanced'
    para['max_iter'] = 1000
    ##-------------------------------    
    pprint.pprint(para)
    ##load data
    #------------------------------load data---------------------------------
    # trainmat = scio.loadmat(trainfilepath) #for v7.0 mat
    trainmat = h5py.File(trainfilepath)
    train_x = trainmat['trainfeature'][:]
    train_y = trainmat['trainlabel'][:]
    videoid = trainmat['trainVideoid'][:]
    train_x = train_x.transpose(1, 0)
    print("training x shape:", train_x.shape)
    print("training y shape:", train_y.shape)
    pdb.set_trace()
    timestart = time.time()
    if isTrain == 1:

        # pdb.set_trace()
        train(x = train_x, y = train_y, saveModelPath = saveModelPath, para = para)
    #-----------------------------------------------------------------------------
    if isTest == 1:
        validationmat = h5py.File(testfilepath)
        # validationmat = scio.loadmat(testfilepath)
        validation_x = validationmat['validationfeature'][:]
        validation_y = validationmat['validationlabel'][:]
        videoid = validationmat['validationVideoid'][:]
        validation_x = validation_x.transpose(1, 0)
        print("testing x shape:", validation_x.shape)
        print("testing y shape:", validation_y.shape)
        print("testing the training data:")
        test_has_gr(x = train_x, y = train_y, modelPath = saveModelPath, saveResultPath = saveResultPath, para = para)
        print("testing the testing data:")
        # test_has_gr(x = validation_x, y = validation_y, modelPath = saveModelPath, saveResultPath = saveResultPath, para = para)
        predict = test_no_gr(x = validation_x, modelPath = saveModelPath, saveResultPath = saveResultPath, para = para)
        Generate_submission_file(videoid = videoid, predict  = predict, mysubfile = submissionFile, GivenVideolistfile = GivenVideolistfile, isTest = 1)
    timeend = time.time()
    print("using time: ", timeend - timestart)