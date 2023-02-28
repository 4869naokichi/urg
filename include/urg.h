/**
 * @file urg.h
 * @brief LRFと通信し、データを読み取る
 * @author naokichi
 * @date 2023/02/27
 */

#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "serialport.h"
#include "speak.h"
#include "timer.h"

/**
 * @brief LRFをセットアップする
 * @retval TRUE 成功
 * @retval FALSE 失敗
 */
BOOL SetupURG();

/**
 * @brief LRFからの電文を受信する
 * @return 受信した電文
 * @note 終端コードはLFLF
 */
std::string ReadLineURG();

/**
 * @brief レーザースキャンデータを取得する
 * @return レーザースキャンデータ（直交座標）
 * @note auto [x, y] = GetScan(); のように戻り値を受け取ってください
 */
std::tuple<std::vector<float>, std::vector<float>> GetScan();

/**
 * @brief LRFから送信されたデータをデコードする
 * @param rawData エンコードされたデータ
 * @return 距離データ
 */
std::vector<int> Decode(std::string rawData);

/**
 * @brief LRFを停止する
 * @retval TRUE 成功
 * @retval FALSE 失敗
 */
BOOL StopURG();