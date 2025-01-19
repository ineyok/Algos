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
ost.insert(x);
ost.erase(x);
*ost.find_by_order(k)
ost.order_of_key(x)
