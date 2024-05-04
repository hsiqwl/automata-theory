#ifndef REGEX_GROUP_INFO_H
#define REGEX_GROUP_INFO_H
#include <vector>

class group_info{
public:
    typedef std::vector<size_t>::iterator iterator;

    typedef std::vector<size_t>::const_iterator const_iterator;

    group_info() = default;

    void add_group(size_t group_number);

    std::pair<const_iterator, const_iterator> get_tracked_groups() const noexcept;

private:
    std::vector<size_t> tracked_groups;
};

#endif //REGEX_GROUP_INFO_H
