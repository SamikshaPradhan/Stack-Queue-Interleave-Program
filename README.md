# Stack-Queue-Interleave-Program
Description: Algorithm to Interleave the first half of the queue with second half
My Encoding Algorithm
Following are the steps used to encode a list of words:
1. Push the first half elements of queue to stack.
2. Enqueue back the stack elements.
3. Dequeue the first half elements of the queue and enqueue them back.
4. Again push the first half elements into the stack.
5. Interleave the elements of queue and stack.

I have an encode data file (a text file of words) that I need decoded.  The algorithm I used to encode the data
is shown above.  Your problem, to decode the encoded data.  The input will be a ‘…txt’ file of words which
consists of a list of words that have been encoded as described above.   Write a program to input the txt file
and print out the decoded results. Restrictions:   You must use aggregate Stack and Queue class. To solve this
problem, you can have ONE Queue and ONE Stack and only one of each.  The input data will be loaded into a Queue
to start with and from the Queue start your algorithm to decode the text.  (Decoding as you read in your data will
not be acceptable.)

Use your own stack and queue class.
