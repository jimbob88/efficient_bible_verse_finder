# Bible Reader

This bible software is an extremely simple bible-reader using data from [ebible.org](https://ebible.org/)!

## Setup
- First of all head to [ebible.org](https://ebible.org/download.php) and get a copy of any bible. For this example I will be using [engwebpb](https://ebible.org/details.php?id=engwebpb). 

- Download the `*_readaloud.zip` option. (For engwebpb this is [here](https://ebible.org/Scriptures/engwebpb_readaloud.zip))

- Create a new folder in the same directory as your `main` or `main.py` called `bibles`. 

i.e:
```
$ mkdir ./bibles
```

- Unzip the `*_readaloud.zip` to a folder with its ID:
```
$ cd ./bibles
$ mkdir engwebpb
$ cd engwebpb
$ unzip ~/Downloads/engwebpb_readaloud.zip
```

- Add a new file called `bibles.txt` in the root folder (with `main` and `main.py`) 
With the ID of your bible:

```
engwebpb
```

## Commands:

Python Usage:
```
usage: main.py [-h] -b BIBLE -B BOOK -n BOOK_NUMBER [-t]

Read the bible!

optional arguments:
  -h, --help            show this help message and exit
  -b BIBLE, --bible BIBLE
                        The bible to open
  -B BOOK, --book BOOK  The book to open
  -n BOOK_NUMBER, --book-number BOOK_NUMBER
                        The book number to open
  -t, --use-txt
```

C Usage:
```
usage: ./main [-h] -b BIBLE -B BOOK -n BOOK_NUMBER

Read the bible!

optional arguments:
  -h, --help            show this help message and exit
  -b BIBLE, --bible BIBLE
                        The bible to open
  -B BOOK, --book BOOK  The book to open
  -n BOOK_NUMBER, --book-number BOOK_NUMBER
                        The book number to open
```

NOTICE: The `-t` option is exclusive to python because it only works in python (currently). 

## Performance
### C
Command: `$ time ./main -b engwebpb -B PSA -n 112`
```
real    0m0.003s
user    0m0.001s
sys     0m0.000s
```
### Python
Command: `$ time python3 main.py -b engwebpb -B PSA -n 112 -t`
```
real    0m0.024s
user    0m0.016s
sys     0m0.008s
```