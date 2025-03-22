#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// множество <int>
using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

// словарь <int, int>
using ordered_map = tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

// мультимножество <int, index>
using ordered_set = tree<pair<int, int>, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;


ordered_set ost;
ost.insert(el);
ost.erase(el);
*ost.find_by_order(index)
ost.order_of_key(el)
