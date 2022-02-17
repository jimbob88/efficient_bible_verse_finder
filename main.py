import argparse
import os
import glob

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Read the bible!")
    parser.add_argument(
        "-b",
        "--bible",
        required=True,
        action="store",
        default=None,
        help="The bible to open",
    )
    parser.add_argument(
        "-B",
        "--book",
        required=True,
        action="store",
        default=None,
        help="The book to open",
    )
    parser.add_argument(
        "-V",
        "--verse",
        type=int,
        required=True,
        action="store",
        default=None,
        help="The verse to open",
    )
    parser.add_argument("-t", "--use-txt", required=False, action="store_true")

    args = parser.parse_args()

    print(f"Checking bible exists: {args.bible}")

    bible_exists = False
    if args.use_txt:
        print("Using ./bibles.txt")
        with open("bibles.txt", "r") as f:
            if args.bible in f.readlines():
                bible_exists = True
    else:
        print("Trying to discover bibles")
        if args.bible in next(os.walk("./bibles"))[1]:
            bible_exists = True

    if not bible_exists:
        raise ValueError(f"{args.bible}: Bible not found")

    glob_result = glob.glob(
        f"./bibles/{args.bible}/{args.bible}_*_{args.book}_{args.verse:02}_read.txt"
    )
    if len(glob_result) < 1:
        glob_result = glob.glob(
            f"./bibles/{args.bible}/{args.bible}_*_{args.book}_{args.verse:03}_read.txt"
        )

    if len(glob_result) < 1:
        raise ValueError(
            f"{args.bible}: No verse found in {args.book} at verse {args.verse}"
        )

    with open(glob_result[0], "r") as f:
        print(f.read())
