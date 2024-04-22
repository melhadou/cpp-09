## Workgin On -

`Merge function` <- **Algo** 
- [x] Case 1: If the first sub-range (begin to savedMiddle) is exhausted, 
        it means all the remaining elements are from the second sub-range 
        (middle to end). In this case, it simply copies the remaining
        elements from the second sub-range to res.

- [x] Case 2: If the second sub-range (middle to end) is exhausted,
        it means all the remaining elements are from the first sub-range
        (begin to savedMiddle). In this case, it copies the remaining 
        elements from the first sub-range to res.

- [x] Case 3: If both sub-ranges have elements remaining, it compares
        the values at begin and middle. If the value at begin is smaller,
        it copies that element to res and increments begin. Otherwise, 
        it copies the element at middle to res and increments middle.

# Resources
https://www.youtube.com/watch?v=-3u1C1URNZY
