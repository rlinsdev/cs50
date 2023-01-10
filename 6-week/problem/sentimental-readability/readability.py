from cs50 import get_string


def main():
    # text = get_string("Text: ")
    text = "Congratulations! Today is your day. You're off to Great Places! You're off and away!"

    qtd_ltt, qtd_stc, qtd_wrd = handle_text(text)
    # print(qtd_ltt)
    # print(qtd_stc)
    # print(qtd_wrd)



def handle_text(txt):
    qtd_ltt = 50
    qtd_stc = 200
    qtd_wrd = 500
    return qtd_ltt, qtd_stc, qtd_wrd




if __name__ == "__main__":
    main()
