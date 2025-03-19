#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// множество <int>
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// словарь <int, int>
typedef tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// мультимножество <int, index>
typedef tree<pair<int, int>, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


ordered_set ost;
ost.insert(el);
ost.erase(el);
*ost.find_by_order(index)
ost.order_of_key(el)
