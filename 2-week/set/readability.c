#include <cs50.h>
#include <stdio.h>

static void handler_text(string txt, int *qtd_ltt, int *qtd_stc, int *qtd_wrd);

int main(void)
{
    int qtd_ltt = 0;
    int qtd_stc = 0;
    int qtd_wrd = 0;
    // string text = get_string("Text: ");
    string text = "Congratulations! Today is your day. You're off to Great Places! You're off and away!";

    handler_text(text, &qtd_ltt, &qtd_stc, &qtd_wrd);

    printf("Quantidade de letra: %i", qtd_ltt);

}

static void handler_text(string txt, int *qtd_ltt, int *qtd_stc, int *qtd_wrd)
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
