# Day 1
  * Q1: count number of palindromes in string
    * manacher/hashing+binary search
  * Q2:
  * Q3: construct string using 2 different characters with len<=1e5 that consists of exactly K<=1e9 subsegments that are palindromes
    * https://pastebin.com/9KQN0YSD (didn't check)
    * basically construct something considering by cutting between different characters aa..a|bb..b|aa..a|bb..b|aa...
# Day 2
  * Q1: https://cdn.discordapp.com/attachments/575910389066235917/582441440790183947/Screen_Shot_2019-05-27_at_01.34.04.png
    * sort by duration desc
    * eliminate R thing by multiplying R to every d
    * only activate spell when time runs out or mana runs out
    * maintain dp1[time left with full mana]=max score and dp2[mana left with no time]=maxscore
  * Q2: "stupid scc" --- Ethan Ypedo Guo 2019
  * Q3: "binary search on output" --- Brian Chau 2019
  * Q4: "find the minimum sum of radii of two circles which enclose all points, N<=200"
    * idk how to solve
# Day 3
  * Q1: Given DAG (N,M<=1e5) and a subset of edges, flip them in some order so that no cycles form in the process.
  * Q2:
    * N,Q<=1e5, Q queries
    * each query given l,r,y<N, add edges between [i,i+y] for all i in [l,r]
    * Find connected components
    * -----------------------
    * break nodes into K blocks
    * handle ranges not in full blocks naively
    * becomes do N/K times this:
    * fixed l,r, add edges for [i,i+y] for all i in [l,r] and y in some set
    * let x be minimum difference between any two elements of y
    * add edges for [i,i+x] for all i in [l,r-x]
    * add edges for [i,i+y] for all i in [l,l+x-1] and y in some set
    * by pigeon-hole principle, complexity is O(N+Q) (with counting sort)
    * by setting K=sqrt(N), overall complexity is O((N+Q)sqrt(N))
  * Q3: 
# Day 4
  * Q1:
  * Q2:
  * Q3:
