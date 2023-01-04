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

    // Grade 3  65 letters, 4 sentences, and 14 words
    // string text = "Congratulations! Today is your day. You're off to Great Places! You're off and away!";

    // // Grade 5. 214 letters, 4 sentences, and 56 words
    // string text = "Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.";

    // Call method to parse the sentence
    handle_text(text, &qtd_ltt, &qtd_stc, &qtd_wrd);
    // Call method to calculate the final grade
    handle_calc(qtd_ltt, qtd_stc, qtd_wrd);
}

/**
 * @brief Handle Calc. Will apply Coleman-Liau formula.
 * Parse to double to avoid mistake in decimal calc
 * @param qtd_ltt Quantity of Letter
 * @param qtd_stc Quantity of Sentence
 * @param qtd_wrd Quantity of Word
 */
static void handle_calc(int qtd_ltt, int qtd_stc, int qtd_wrd)
{
    double letter_per_hundred_words = ((double)qtd_ltt / qtd_wrd * 100);
    double sentence_per_hundred_words = ((double)qtd_stc / qtd_wrd * 100);

    // Get decimal places
    double result = ((double)(0.0588 * letter_per_hundred_words - 0.296 * sentence_per_hundred_words - 15.8));

    if (result >= 16)
    {
        printf("Grade 16+");
    }
    else if (result < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        // Round the result
        printf("Grade %.0f\n", result);
    }
}

/**
 * @brief Will pass through word by word in text to find: Word, Sentence and
 * letter. Handle 3 dots (...)
 * @param txt Text to be handler
 * @param qtd_ltt Quantity of Letter
 * @param qtd_stc Quantity of Sentence
 * @param qtd_wrd Quantity of Word
 */
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
