/**
 * @file timer.h
 * @brief 処理時間を計測する
 * @author naokichi
 * @date 2023/02/27
 */

#pragma once

#include <iostream>
#include <windows.h>

/** 処理時間を計測するクラス */
class Timer {
public:
  /**
   * コンストラクタ
   */
  Timer();

  /**
   * @brief タイマーをリスタートする
   */
  void Restart();

  /**
   * @brief 経過時間を取得する
   * @return 経過時間 [s]
   */
  double GetElapsedTime();

private:
  LARGE_INTEGER freq;
  LARGE_INTEGER start, end;
};
