----------------------------------------------------------------------------------
| Question 1: Which data structure performs faster on inventory lookups and why? |
----------------------------------------------------------------------------------
    - In our experience, we found that the ##binary search tree## was faster than
      the linked list in conducting inventory lookups. This is all to do with the
      difference in the average time complexity of the different data structures. 
      
    - With the BST, the nodes are sorted based on the value of the data they store.
      Because of this, we can more accurately traverse a dataset based on the datum
      stored in a specific node and comparing that value to our target.
      
    - This ability to dynamically determine which way to traverse our data structure
      based on the information at hand allows the average time complexity of looking 
      data up of our binary search tree to be O(log(N)), as opposed to the average 
      time complexity of O(N) for the single linked list.

    - The difference in time complexity between our data structures grows increasingly 
      apparent as the number of operations grows in size.


-----------------------------------------------------------------------------------------------
| Question 2: Report execution times for each data structures required on tests 1, 6, 7, 8, 9 |
-----------------------------------------------------------------------------------------------
Test Number:                 Single Linked List (SLL)                  Binary Search Tree (BST)
############                 ########################                  ########################
    1                            0.0362367 seconds                        0.000077667 seconds  
    6                            1.15081   seconds                        0.00157429  seconds 
    7                            6.48915   seconds                        0.0129415   seconds
    8                           61.381     seconds                        0.481246    seconds
    9                          668.058     seconds                       40.5114      seconds
     

---------------------------------------------------------------------------
| Question 3: What might be a consequence of making the inventory sorted? |
---------------------------------------------------------------------------
    - In the case of a binary search tree having the inventory sorted in 
      increasing order would cause the next node to always be bigger than 
      the previous one, hence placed on the right. This would effectively 
      make the tree into a single linked list, lowering the average lookup 
      time from O(log(N)) to O(N). For the single linked list, the average 
      lookup time stays at O(N).
      

----------------------------------------------------------------------------------------------------  
| Question 4: What Linux command(s) might one use to monitor the performance of a running process? |
----------------------------------------------------------------------------------------------------
    - top 