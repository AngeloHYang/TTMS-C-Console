/*
Rating symbol	Meaning
G rating symbol
G 每 General Audiences
All ages admitted. Nothing that would offend parents for viewing by children.
PG- rating symbol
PG 每 Parental Guidance Suggested
Some material may not be suitable for children. Parents urged to give "parental guidance". May contain some material parents might not like for their young children.
PG-13 rating symbol
PG-13 每 Parents Strongly Cautioned
Some material may be inappropriate for children under 13. Parents are urged to be cautious. Some material may be inappropriate for pre-teenagers.
R rating symbol
R 每 Restricted
Under 17 requires accompanying parent or adult guardian. Contains some adult material. Parents are urged to learn more about the film before taking their young children with them.
NC-17 rating symbol
NC-17 每 Adults Only
No One 17 and Under Admitted. Clearly adult. Children are not admitted.
*/

#ifndef _enum_play_rating_t
#define _enum_play_rating_t
typedef enum {
	PLAY_RATE_G = 1,
	PLAY_RATE_PG = 2,
	PLAY_RATE_PG13 = 3,
	PLAY_RATE_R = 4,
	PLAY_RATE_NC_17 = 5
}play_rating_t;

#endif // !1