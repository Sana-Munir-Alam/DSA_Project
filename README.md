# Memory Match Game (Doubly Linked List Version)

## Project Plan

Let's start with just the **C++ code** without any GUI for now, to help us understand the program flow.
We will begin with **10 unique cards**, represented by the letters **A to J** (just an example).  
Since each unique card needs a pair for matching, there will be a total of **20 nodes** in our **doubly linked list**.  
Every time the program is executed, these card nodes will be **inserted randomly** inside the linked list. (this will bring uniqueness, and randomness)

---

## Game Logic

- The list will be displayed initially with all cards **face down**, marked as `'X'`. (flip status will be false)
- The user will then enter a **node position** (for example, `3`).
- The list will be traversed to that position from head(1), and the corresponding card will be **flipped**, showing its value while its flipped status is set to `true`.
- The terminal will then prompt for the **second card position**.
- If the user re-enters a position that is already flipped (for example, entering `3` again),  
  an **error message** will be shown, and the user will be asked to enter a **different position**. (the previous card will still remain flipped)
- If both flipped cards have the **same value**, the user:
  - Earns **+1 point**.
  - The two matched cards are **removed** from the list (so now 18 cards remain instead of 20).
- If the tiles **do not match**, both cards’ flipped status will be reset to `false`,  
  and the list will again be displayed with all cards marked as `'X'`.
- This process will continue until **all cards are matched and removed** from the list.

---

## Example Run

*(Example uses 10 cards for simplicity, as displaying 20 would be too long)*

    Head  2   3   4   5   6   7   8   9  Tail
NULL<-X<->X<->X<->X<->X<->X<->X<->X<->X<->X->NULL  *(List of 10 cards displayed initially all downturned)*

<br>Enter Position Number: 3
<br>NULL<-X<->X<->A<->X<->X<->X<->X<->X<->X<->X->NULL
<br>Enter Position Number: 7
<br>NULL<-X<->X<->A<->X<->X<->X<->A<->X<->X<->X->NULL
<br>GREAT, THE TILES MATCH. PLUS 1 POINT
<br>Score: 1
<br><br>NULL<-X<->X<->X<->X<->X<->X<->X<->X<->NULL *(List updated to 8 as the two matched cards have been removed)*
<br>Enter Position Number: 3# Memory Match Game (Doubly Linked List Version)

## Project Plan

Let's start with just the **C++ code** without any GUI for now, to help us understand the program flow.  
We will begin with **10 unique cards**, represented by the letters **A to J** (just an example).  
Since each unique card needs a pair for matching, there will be a total of **20 nodes** in our **doubly linked list**.  
Every time the program is executed, these card nodes will be **inserted randomly** inside the linked list.  
*(This will bring uniqueness and randomness.)*

---

## Game Logic

- The list will be displayed initially with all cards **face down**, marked as `'X'` (flip status will be false).  
- The user will then enter a **node position** (for example, `3`).  
- The list will be traversed to that position from **head (1)**, and the corresponding card will be **flipped**, showing its value while its flipped status is set to `true`.  
- The terminal will then prompt for the **second card position**.  
- If the user re-enters a position that is already flipped (for example, entering `3` again), an **error message** will be shown, and the user will be asked to enter a **different position** (the previous card will still remain flipped).  
- If both flipped cards have the **same value**, the user:  
  - Earns **+1 point**.  
  - The two matched cards are **removed** from the list (so now 18 cards remain instead of 20).  
- If the tiles **do not match**, both cards’ flipped status will be reset to `false`, and the list will again be displayed with all cards marked as `'X'`.  
- This process will continue until **all cards are matched and removed** from the list.  

---

## Example Run

*(Example uses 10 cards for simplicity, as displaying 20 would be too long.)*

**Initial State:**

Head 2 3 4 5 6 7 8 9 Tail  
`NULL <- X <-> X <-> X <-> X <-> X <-> X <-> X <-> X <-> X <-> X -> NULL`  
*(List of 10 cards displayed initially, all downturned)*  

**Enter Position Number: 3**  
`NULL <- X <-> X <-> A <-> X <-> X <-> X <-> X <-> X <-> X <-> X -> NULL`  

**Enter Position Number: 7**  
`NULL <- X <-> X <-> A <-> X <-> X <-> X <-> A <-> X <-> X <-> X -> NULL`  
**GREAT, THE TILES MATCH. PLUS 1 POINT**  
**Score: 1**  

`NULL <- X <-> X <-> X <-> X <-> X <-> X <-> X <-> X <-> NULL`  
*(List updated to 8 as the two matched cards have been removed)*  

---

**Enter Position Number: 3**  
`NULL <- X <-> X <-> D <-> X <-> X <-> X <-> X <-> X <-> NULL`  

**Enter Position Number: 3**  
`NULL <- X <-> X <-> D <-> X <-> X <-> X <-> X <-> X <-> NULL`  
**ERROR, CARD ALREADY FLIPPED. SELECT A NEW ONE**  

**Enter Position Number: 8**  
`NULL <- X <-> X <-> D <-> X <-> X <-> X <-> B <-> X <-> NULL`  
**THE TILES DON’T MATCH**  
**Score: 1**  

`NULL <- X <-> X <-> X <-> X <-> X <-> X <-> X <-> X <-> NULL`  

---

**Enter Position Number: 3**  
`NULL <- X <-> X <-> D <-> X <-> X <-> X <-> X <-> X <-> NULL`  

**Enter Position Number: 1**  
`NULL <- D <-> X <-> D <-> X <-> X <-> X <-> X <-> X -> NULL`  
**GREAT, THE TILES MATCH. PLUS 1 POINT**  
**Score: 2**  

`NULL <- X <-> X <-> X <-> X <-> X <-> X <-> NULL`  

---

*The game will continue in this pattern until all nodes are matched and removed.*
<br>Once the list is empty, the game ends, and the final score is displayed.
