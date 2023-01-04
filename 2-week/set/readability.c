#include <cs50.h>
#include <stdio.h>

static void handle_text(string txt, int *qtd_ltt, int *qtd_stc, int *qtd_wrd);
static void handle_calc(int qtd_ltt, int qtd_stc, int qtd_wrd);

int main(void)
{
    int qtd_ltt = 0;
    int qtd_stc = 0;
    int qtd_wrd = 1;
    // string text = get_string("Text: ");
    string text = "Congratulations! Today is your day. You're off to Great Places! You're off and away!";

    handle_text(text, &qtd_ltt, &qtd_stc, &qtd_wrd);
    handle_calc(qtd_ltt, qtd_stc, qtd_wrd);
}

static void handle_calc(int qtd_ltt, int qtd_stc, int qtd_wrd)
{
    double letter_per_hundred_words = ((double)qtd_ltt / qtd_wrd * 100);
    double sentence_per_hundred_words = ((double)qtd_stc / qtd_wrd * 100);

    int result = (0.0588 * letter_per_hundred_words - 0.296 * sentence_per_hundred_words - 15.8);

    printf("Grade %i\n", result);
}

static void handle_text(string txt, int *qtd_ltt, int *qtd_stc, int *qtd_wrd)
{
    int i = 0;
    while (txt[i])
    {
        // Simulate isAlpha func.
        if((txt[i] >= 'a' && txt[i] <= 'z') || (txt[i] >= 'A' && txt[i] <= 'Z'))
        {
            // +1 Letter
            *qtd_ltt = *qtd_ltt + 1;
        }
        else if (txt[i] == ' ')
        {
            // +1 word
            *qtd_wrd = *qtd_wrd + 1;
        }
        // Check end of sentence.
        else if(txt[i] == '!' || txt[i] == '.' || txt[i] == '?'
                || txt[i] == ':')
        {
            // Handle '...'. Just one sentence. Increment 'i' variable.
            if ((txt[i+1] && txt[i+2]) && (txt[i] == '.' && txt[i+1] == '.'
                    && txt[i+2] == '.'))
            {
                i = i + 2;
            }
            // +1 Sentence
            *qtd_stc = *qtd_stc + 1;
        }
        i++;
    }
}
