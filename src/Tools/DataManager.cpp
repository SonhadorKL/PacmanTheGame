#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <time.h>

#include "DataManager.h"
#include "DataConfig.h"
using json = nlohmann::json;

std::vector<std::string> JsonManager::get_data(int symbol_count) {
    std::vector<std::string> result;
    auto gaps = read_records();
    sort_data(gaps);
    size_t cur_ind = 1;
    for (auto& info : gaps) {
        std::string just_another_str = format_string(info, cur_ind, symbol_count);
        result.push_back(just_another_str);
        ++cur_ind; 
    }
    return result;
}

void JsonManager::clear_data() {
    std::ofstream file(kPathToData + "/records.json");
    json js;
    file << js;
    file.close();
}

bool JsonManager::set_data(int record) {
    auto records = read_records();
    Information new_record{ record, currentDateTime() };
    records.push_back(new_record);
    sort_data(records);
    
    bool is_record = records.front() == new_record;
    if (records.size() > pacg::table_max_size) {
        records.pop_back();
    }
    
    write_records(records);
    return is_record;
}

auto JsonManager::read_records() -> std::vector<Information> {
    std::ifstream file(kPathToData + "/records.json");
    json data_file;
    if (file.is_open()) {
        file >> data_file;
        file.close();
    }
    std::vector<Information> info;
    for (const auto& d : data_file) {
        info.push_back({d["score"], d["date"]});
    }
    return info;
}

void JsonManager::write_records(const std::vector<Information>& records) {
    json new_records;
    size_t cur_index = 1;
    for (auto& rec : records) {
        new_records[std::to_string(cur_index)] = { {"date", rec.date}, {"score", rec.score} };
        ++cur_index; 
    }
    std::ofstream file(kPathToData + "/records.json");
    file << new_records;
    file.close();
}

void JsonManager::sort_data(std::vector<Information>& info) {
    std::sort(info.begin(), info.end());
}

std::string JsonManager::format_string(const Information & info, size_t index, size_t max_len) {
    const size_t kBaseLen = 3;
    size_t substr_len = info.date.size() + std::to_string(info.score).size() + (index > 9 ? kBaseLen + 1 : kBaseLen);
    size_t len = (substr_len >= max_len ? 1 : max_len - substr_len);
    return std::to_string(index) + ". " + info.date + std::string(len, ' ') + std::to_string(info.score);
}

const std::string currentDateTime() {
  std::time_t t = std::time(nullptr);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&t));
  return buffer;
}

