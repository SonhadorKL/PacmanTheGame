#include <vector>
#include <string>
#include "General.h"


// Return data in YYYY-MM-DD
const std::string currentDateTime();

// Interface to get data about user's records
class ReadRecords {
public:
    // Return strings - information about users recors   
    virtual std::vector<std::string> get_data(int symbol_count) = 0;
};

// Interface to write data about user's records
class WriteRecord {
public:
    // clear data
    virtual void clear_data() = 0;
    // Try to update data in table
    virtual bool set_data(int record) = 0;
};

// Store data in json-format
class JsonManager : public WriteRecord, ReadRecords {
private:
    struct Information;
public:
    std::vector<std::string> get_data(int symbol_count) override;
    void clear_data() override;
    bool set_data(int record) override;

private:
    // Get vector with information
    std::vector<Information> read_records();
    // Rewrite data
    void write_records(const std::vector<Information>& records);
    // Just sort vector
    void sort_data(std::vector<Information>& info);
    std::string format_string(const Information& info, size_t index, size_t max_len);
    
    struct Information {
        int score;
        std::string date;
        bool operator<(const Information& other) { return score > other.score; }
        bool operator==(const Information& other) { return score == other.score && date == other.date; }
    };
};