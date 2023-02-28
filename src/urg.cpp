/**
 * @file urg.h
 * @brief LRFと通信し、データを読み取る
 * @author naokichi
 * @date 2023/02/27
 */

#include <urg.h>

/**
 * @brief LRFをセットアップする
 * @retval TRUE 成功
 * @retval FALSE 失敗
 */
BOOL SetupURG() {
  BOOL retval;
  retval = SetupComPort("COM5", 115200);
  if (retval == FALSE) {
    return FALSE;
  }
  retval = WriteLine("SCIP2.0\n");
  if (retval == FALSE) {
    return FALSE;
  }
  ReadLineURG();
  retval = WriteLine("BM\n");
  if (retval == FALSE) {
    return FALSE;
  }
  ReadLineURG();
  return TRUE;
}

/**
 * @brief LRFからの電文を受信する
 * @return 受信した電文
 * @note 終端コードはLFLF
 */
std::string ReadLineURG() {
  std::string rxData;
  for (int i = 0; i < 4096; i++) {
    rxData += ReadByte();
    if (rxData.ends_with("\n\n")) break;
  }
  rxData.pop_back();  // LFを取り除く
  return rxData;
}

/**
 * @brief レーザースキャンデータを取得する
 * @return レーザースキャンデータ（直交座標）
 * @note auto [x, y] = GetScan(); のように戻り値を受け取ってください
 */
std::tuple<std::vector<float>, std::vector<float>> GetScan() {
  WriteLine("GD0000108000\n");
  std::string rxData = ReadLineURG();

  std::stringstream ss(rxData);
  std::vector<std::string> blocks;
  std::string block;
  while (std::getline(ss, block, '\n')) {
    blocks.push_back(block);
  }

  std::string rawRangeData;
  for (size_t i = 3; i < blocks.size(); i++) {
    blocks[i].pop_back();  // チェックサムを取り除く
    rawRangeData += blocks[i];
  }

  std::vector<int> ranges = Decode(rawRangeData);
  std::vector<float> angles;
  for (size_t i = 0; i < ranges.size(); i++) {
    float angle = -M_PI_4 + (2.0f * M_PI / 1440.0f) * i;
    angles.push_back(angle);
  }

  std::vector<float> x, y;
  for (size_t i = 0; i < ranges.size(); i++) {
    x.push_back(ranges[i] * std::cos(angles[i]));
    y.push_back(ranges[i] * std::sin(angles[i]));
  }
  return {x, y};
}

/**
 * @brief LRFから送信されたデータをデコードする
 * @param rawData エンコードされたデータ
 * @return 距離データ
 */
std::vector<int> Decode(std::string rawData) {
  std::vector<int> ranges;
  for (auto& c : rawData) {
    c -= 0x30;
  }
  for (size_t i = 0; i < rawData.size(); i += 3) {
    std::string str = rawData.substr(i, 3);
    int range = str[0] << 12 | str[1] << 6 | str[2];
    ranges.push_back(range);
  }
  return ranges;
}

/**
 * @brief LRFを停止する
 * @retval TRUE 成功
 * @retval FALSE 失敗
 */
BOOL StopURG() {
  BOOL retval = WriteLine("QT\n");
  return retval;
}