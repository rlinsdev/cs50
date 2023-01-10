from cs50 import get_string


def main():
    text = get_string("Text: ")

    qtd_ltt, qtd_stc, qtd_wrd = handle_text(text)
    handle_calc(qtd_ltt, qtd_stc, qtd_wrd)


def handle_text(txt):

    # Initialize variables
    qtd_wrd = 0
    qtd_ltt = 0
    qtd_stc = 0

    # word
    qtd_wrd = len(txt.split())

    # Verify Sentence
    for c in txt:
        if c == "." or c == "!" or c == "?":
            qtd_stc += 1
        elif c.isalpha():
            qtd_ltt += 1

    # Return results
    return qtd_ltt, qtd_stc, qtd_wrd


def handle_calc(qtd_ltt, qtd_stc, qtd_wrd):
    letter_per_hundred_words = float(qtd_ltt / qtd_wrd * 100)
    sentence_per_hundred_words = float(qtd_stc / qtd_wrd * 100)

    result = float(0.0588 * letter_per_hundred_words - 0.296 * sentence_per_hundred_words - 15.8)
    int_result = round(result)

    if int_result >= 16:
        print("Grade 16+")
    elif int_result < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {int_result}")


if __name__ == "__main__":
    main()
