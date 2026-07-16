# Debugging the Quicksort Program

After studying the simulation of the quicksort algorithm, I reached the following conclusion: 

An item in the list (the first one in this case) is chosen as the pivot, and the left and right ends of the list are used as boundaries. By using this method, the pivot will always be located at one of those two bounds. The two are then compared to see if the item at the left bound is smaller than the right bound, as it should be. If so, nothing changes, but if the items are backwards, they switch places. In either case, whichever bound is currently not the pivot is shifted one index closer to the pivot, with the left bound shifting right and the right bound shifting left. This continues until the two bounds sit on the same index. By this point, the pivot will be in its final position, all items to its left belong to its left, and all items to its right belong to its right. For example, in a list of numbers 1-15 where the first pivot selected is 6, once the two bounds meet, 6 will be in the sixth spot of the list, 1-5 will be on the left and 7-15 will be on the right. The pivot will then be saved somewhere to recognize that it has already been sorted, and the process will loop until every item has served as the pivot at one point. 

My original analysis of the quicksort simulator did not take into account a recursive approach, nor had I been taught anything about recursion in programming at the time, so the primary challenge seemed to be finding a way to keep track of what indexes hold items that were previously used as the pivot, as those items inevitably reach their final positions after being used as the pivot. As a solution, I created a secondary list of equal length to the test array in the form of a global variable that would store the final index of each pivot that gets used. Because both the test array's contents and its length were always hard-coded, this method wasn't inherently problematic. However, I eventually would discover that this secondary array was the root of the bug I was trying to fix. 

Here is a list of the steps taken in the original version, and the nature of the bug that we are attempting to fix: 

1. Initialize all variables and custom functions, including the test array, the two bounds, and the custom Quicksort class instance.
2. Display the initial array to show the starting point of the sort.
3. While the list is unsorted and the loop iterations have not exceeded the length of the list:
  1. Define a pointer to represent the next iteration of the list.
  2. Call the "sort" function to assign its returned value to the pointer:
     1. Set the left bound to the leftmost item whose index is not included in the array of former pivots.
     2. Find the immediate next index that has been used as a pivot before, and set the right bound equal to the index to its immediate left. For example, if index 7 is the nearest former pivot, set the right bound to 6.
     3. Save the current pivot to a variable (hold) and let 0 be used in its place in the list. This only works as long as 0 is not an existing list item, and 0 will indicate the current location of the pivot. 
     4. If the pivot is currently on the wrong side of the opposite bound, swap the bound with the 0.
     5. If the 0 is currently on the left side, move the right bound index 1 to the left. If the 0 is to the right, move the left bound index 1 to the right.
     6. Repeat 4-5 until the bound indexes match. After the loop ends, return the pivot to that position in the list and remove the 0. All list items should be correctly arranged relative to the pivot's proper position.
     7. Add the pivot's index to the secondary array. 
     8. RETURN the new version of the list. 
  3. Iteratively assign each item in the pointer's returned array to the original array.
  4. Display the new list. 
  5. Call the "isSorted" function to evaluate the array's status and update the status boolean variable.
4. When the loop is finished, display the final version of the array

BUG: After reaching the 4th iteration of the outermost loop, the array no longer experiences any changes. 

---

Failing on the first iteration would be understandable, as most bugs in code take place regardless of loops. The second iteration, also not that strange, as it likely means the loop(s) has an unforeseen influence on the program. However, passing three entire iterations without issue and struggling on the fourth made almost no sense, and I had not developed the programming-oriented thought process to explore all potential causes. 

* Attempt 1: Run the program again in case it was a 'heisenbug'
  * FAIL: The bug was in the actual code, not just a bad run.
* Attempt 2: Introduce the custom class to handle the bound selection in the sorting method
  * FAIL: Though still a great decision, the bound selection was not the issue. It only simplified the code file I was working in without solving the issue. 
