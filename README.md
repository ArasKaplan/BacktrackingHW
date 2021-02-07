# BacktrackingHW
A C program that uses backtracking to solve a sudoku-like puzzle

Problem: NxN’lik bir matris görünümündeki oyun tahtasında her satırda aynı N
renk farklı sıra ile yer almaktadır. Bir satırdaki renklerin sıralanışı, renkler sağa
doğru kaydırılarak değiştirilebilmektedir. Örneğin satırdaki renkler sırası ile
kırmızı, mavi, yeşil, mor ise satır 1 defa sağa kaydırıldığında yeni sıralama mor,
kırmızı, mavi, yeşil olur. Bir defa daha sağa kaydırılırsa yeşil, mor, kırmızı,
mavi elde edilir. Sonuç matrisinde her sütunda her renkten sadece 1 tane olacak
şekilde satırları geri-izleme(backtracking) yöntemi ile rekürsif olarak
düzenleyen algoritmayı tasarlayınız.
