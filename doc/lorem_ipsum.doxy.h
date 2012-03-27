/**
 * @addtogroup LoremIpsum Lorem Ipsum
 * @ingroup Modules
 *
 * The LoremIpsum module can be used to generate filler text when you need
 * to work on the layout of a document.
 *
 * The generated text does not mean anything, so the reader won't be distracted
 * by the contents when looking at the page layout. Your document will look
 * like normal English (or rather, Latin) because the letter distribution in
 * Lorem Ipsum is close to natural language.
 *
 * The generated text can be arbitrarily long; the lorem_ipsum function will
 * simply repeat the sequence as necessary. The base sequence has a length of
 * 69 words and is as follows:
 *
@verbatim
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do
eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut
enim ad minim veniam, quis nostrud exercitation ullamco laboris
nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor
in reprehenderit in voluptate velit esse cillum dolore eu fugiat
nulla pariatur. Excepteur sint occaecat cupidatat non proident,
sunt in culpa qui officia deserunt mollit anim id est laborum.
@endverbatim
 *
 * Here is an example:
 *
@code
import LoremIpsum 1.0

writeln lorem_ipsum 30
writeln "----"
writeln lorem_ipsum 30, 3
@endcode
 *
 * The above code generates the following output:
 *
@verbatim
Lorem ipsum dolor sit amet, consectetur adipisicing elit,
sed do eiusmod tempor incididunt ut labore et dolore magna
aliqua. Ut enim ad minim veniam, quis nostrud exercitation
ullamco laboris nisi.
----
Lorem ipsum dolor sit amet.

Consectetur ipsum dolor sit amet.

Eiusmod ipsum dolor sit amet, consectetur adipisicing.
@endverbatim
 *
 * @{
 */

/**
 * Produces a sequence of words in pseudo-latin.
 * The text contains an arbitrary number of words, specified by @a words.
 */
text lorem_ipsum(integer words);


/**
 * Produces a sequence of paragraphs in pseudo-latin.
 * @a words is the total number of words. The text is split in @a para
 * paragraphs of approximately the same length. Paragraphs are separated by
 * two consecutive carriage returns.
 */
text lorem_ipsum(integer words, integer para);

/**
 * @}
 */
