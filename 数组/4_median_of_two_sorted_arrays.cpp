#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

/**
 * 如果直接暴力破解，思路很简单，直接一个个比较，直到第(m+n)/2个元素，但是时间复杂度为O(m+n)
 * 但题目要求的时间复杂度为log(m+n)，同时两个数组是有序的，这也提示了使用二分查找思路
 * 求median元素实际上是求第(m+n)/2大的元素，问题可以拓展为查找两个数组中第k大的元素
 * 考虑这种思路，每次比较nums1和nums2中的第k/2个元素，比较他们的大小
 *      若相等，则这两个元素的值就是整个数组的中间值
 *      若nums1[k/2]>nums2[k/2]，则说明整个数组的topK个元素中(这里的top显然是元素越小越top)，nums2的前k/2个
 *      元素一定在topk元素中，反证可轻易证明这一点，因此这部分元素中肯定没有第topK个元素，并且比第topK个元素小
 *      因此从剩下的B[k/2:]和整个A数组中找第k/2个元素即为所求
 *      若nums1[k/2]<nums2[k/2]，同理，nums1的前k/2个元素一定在整体的topK元素内，因此从剩下的元素中，找到整体的第k/2个元素
 * 还要注意的是当元素个数为偶数时，取中间两个元素的平均数
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>  &nums1, vector<int> &nums2);
};

double Solution::findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
	// 注意总元素的个数为奇数还是偶数，为偶数则取中间两个数的均值
	// 题目中假定了两个vector均非空(即一共至少两个元素)，因此这里不做判断
	// 先取第k/2个元素，如果元素总个数为偶数，则再取第k+1个元素(这里是次序而非下标，下标要-1)
	int i = 0, j = 0;
	int k = (nums1.size() + nums2.size()) / 2;
	// 找到第k个元素
	int var1, var2;
	while (k--) {
		if (i < nums1.size() && j < nums2.size()) {
			if (nums1[i] <= nums2[j])
				var1 = nums1[i++];
			else
				var1 = nums2[j++];
		} else if (i >= nums1.size()) {
			var1 = nums2[j++];
		} else {
			var1 = nums1[i++];
		}
	}
	// 找到第k+1个元素，因为，如果元素总数为奇数，则应该返回第k+1个元素
	// 否则返回两者均值
	if (i >= nums1.size())
		var2 = nums2[j];
	else if (j >= nums2.size())
		var2 = nums1[i];
	else 
		var2 = min(nums1[i], nums2[j]);
	if ((nums1.size() + nums2.size()) % 2)
		return double(var2);
	// cout << "Two vars : " << var1 << ' ' << var2 << endl;
	return (var1 + var2) / 2.0;
}

int main(int argc, char *argv[]) {
	vector<int> nums1 = {1,2};
	vector<int> nums2 = {3,4};
	Solution solution;
	cout << "The median is " << solution.findMedianSortedArrays(nums1, nums2) << endl;
	return 0;
}
