#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// множество <int>
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// словарь <int, int>
typedef tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// мультимножество <int, index>
typedef tree<pair<int, int>, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


ordered_set X;
X.insert(1);
*X.find_by_order(1)
X.order_of_key(-5)<<endl
