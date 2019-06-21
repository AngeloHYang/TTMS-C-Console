#include <stdio.h>
#include "printChoices.h"
#include <conio.h>

void printBatman(int startBy)
{

	printMultipleTimes(' ', startBy);
	printf("       _==/          i     i          \\==_      \n");
	printMultipleTimes(' ', startBy);
	printf("     /XX/            |\\___/|            \\XX\\   \n");
	printMultipleTimes(' ', startBy);
	printf("   /XXXX\\            |XXXXX|            /XXXX\\   \n");
	printMultipleTimes(' ', startBy);
	printf("  |XXXXXX\\_         _XXXXXXX_         _/XXXXXX| \n");
	printMultipleTimes(' ', startBy);
	printf(" XXXXXXXXXXXxxxxxxxXXXXXXXXXXXxxxxxxxXXXXXXXXXXX  \n");
	printMultipleTimes(' ', startBy);
	printf("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|   \n");
	printMultipleTimes(' ', startBy);
	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    \n");
	printMultipleTimes(' ', startBy);
	printf("|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|    \n");
	printMultipleTimes(' ', startBy);
	printf(" XXXXXX/^^^^^\\XXXXXXXXXXXXXXXXXXXXX/^^^^^\\XXXXXX   \n");
	printMultipleTimes(' ', startBy);
	printf("  |XXX|       \\XXX/^^\\XXXXX/^^\\XXX/       |XXX|    \n");
	printMultipleTimes(' ', startBy);
	printf("    \\XX\\       \\X/    \\XXX/    \\X/       /XX/      \n");
	printMultipleTimes(' ', startBy);
	printf("       \"\\       \"      \\X/      \"       /\"        \n");

}

// 100 letters at most!

int main()
{
	extern void all_Load();
	all_Load();

	extern void test();
	test();

	system("cls");
	printMultipleTimes('\n', 5);
	printBatman(25);
	printMultipleTimes('\n', 5);
	printMiddleAddjusted("Welcome to TTMS!", 17);
	printMultipleTimes('\n', 5);

	keyToContinue("Enter", 5);
	
	extern void login();
	login();

	extern void all_Save();
	all_Save();
	
	return 0;
}

/*
quu..__
 $$$b  `---.__
  "$$b        `--.                          ___.---uuudP
   `$$b           `.__.------.__     __.---'      $$$$"              .
	 "$b          -'            `-.-'            $$$"              .'|
	   ".                                       d$"             _.'  |
		 `.   /                              ..."             .'     |
		   `./                           ..::-'            _.'       |
			/                         .:::-'            .-'         .'
		   :                          ::''\          _.'            |
		  .' .-.             .-.           `.      .'               |
		  : /'$$|           .@"$\           `.   .'              _.-'
		 .'|$u$$|          |$$,$$|           |  <            _.-'
		 | `:$$:'          :$$$$$:           `.  `.       .-'
		 :                  `"--'             |    `-.     \
		:##.       ==             .###.       `.      `.    `\
		|##:                      :###:        |        >     >
		|#'     `..'`..'          `###'        x:      /     /
		 \                                   xXX|     /    ./
		  \                                xXXX'|    /   ./
		  /`-.                                  `.  /   /
		 :    `-  ...........,                   | /  .'
		 |         ``:::::::'       .            |<    `.
		 |             ```          |           x| \ `.:``.
		 |                         .'    /'   xXX|  `:`M`M':.
		 |    |                    ;    /:' xXXX'|  -'MMMMM:'
		 `.  .'                   :    /:'       |-'MMMM.-'
		  |  |                   .'   /'        .'MMM.-'
		  `'`'                   :  ,'          |MMM<
			|                     `'            |tbap\
			 \                                  :MM.-'
			  \                 |              .''
			   \.               `.            /
				/     .:::::::.. :           /
			   |     .:::::::::::`.         /
			   |   .:::------------\       /
			  /   .''               >::'  /
			  `',:                 :    .'
								   `:.:'
								   */

								   /*
																		 .,.               .,;;;;;,
																		;;;;;;;,,        ,;;%%%%%;;
																		 `;;;%%%%;;,.  ,;;%%;;%%%;;
																		   `;%%;;%%%;;,;;%%%%%%%;;'
																			 `;;%%;;%:,;%%%%%;;%%;;,
																				`;;%%%,;%%%%%%%%%;;;
																				   `;:%%%%%%;;%%;;;'
											   ..,,,.                                 .:::::::.
											.;;;;;;;;;;,.                                  s.
											`;;;;;;;;;;;;;,                               ,SSSs.
											  `:.:.:.:.:.:.:.                            ,SSSSSSs.
											   .;;;;;;;;;;;;;::,                        ,SSSSSSSSS,
											  ;;;;;;;;;;;;;;;;:::%,                    ,SS%;SSSSSSsS
											 ;;;;;;,:,:::::::;::::%%,                  SS%;SSSSSSsSS
											 ;;;;;,::a@@@@@@a::%%%%%%%,.   ...         SS%;SSSSSSSS'
											 `::::::@@@@@@@@@@@a;%%%%%%%%%'  #;        `SS%;SSSSS'
									  .,sSSSSs;%%,::@@@@@@;;' #`@@a;%%%%%'   ,'          `S%;SS'
									sSSSSSSSSSs;%%%,:@@@@a;;   .@@@a;%%sSSSS'           .%%%;SS,
									`SSSSSSSSSSSs;%%%,:@@@a;;;;@@@;%%sSSSS'        ..,,%%%;SSSSSSs.
									  `SSSSSSSSSSSSs;%%,%%%%%%%%%%%SSSS'     ..,,%;sSSS;%;SSSSSSSSs.
										 `SSSSSSSSSSS%;%;sSSSS;""""   ..,,%sSSSS;;SSSS%%%;SSSSSSSSSS.
											 """""" %%;SSSSSS;;%..,,sSSS;%SSSSS;%;%%%;%%%%;SSSSSS;SSS.
													`;SSSSS;;%%%%%;SSSS;%%;%;%;sSSS;%%%%%%%;SSSSSS;SSS
													 ;SSS;;%%%%%%%%;%;%sSSSS%;SSS;%%%%%%%%%;SSSSSS;SSS
													 `S;;%%%%%%%%%%%%%SSSSS;%%%;%%%%%%%%%%%;SSSSSS;SSS
													  ;SS;%%%%%%%%%%%%;%;%;%%;%%%%%%%%%%%%;SSSSSS;SSS'
													  SS;%%%%%%%%%%%%%%%%%%%;%%%%%%%%%%%;SSSSSS;SSS'
													  SS;%%%%%%%%%%%%%%%%%%;%%%%%%%%%%%;SSSSS;SSS'
													  SS;%%%%%%%%%%%%%;sSSs;%%%%%%%%;SSSSSS;SSSS
													  `SS;%%%%%%%%%%%%%%;SS;%%%%%%;SSSSSS;SSSS'
													   `S;%%%%%%%%%%%%%%%;S;%%%%%;SSSS;SSSSS%
														`S;%;%%%%%%%%%%%'   `%%%%;SSS;SSSSSS%.
														,S;%%%%%%%%%%;'      `%%%%%;S   `SSSSs%,.
													  ,%%%%%%%%%%;%;'         `%;%%%;     `SSSs;%%,.
												   ,%%%%%%;;;%;;%;'           .%%;%%%       `SSSSs;%%.
												,%%%%%' .%;%;%;'             ,%%;%%%'         `SSSS;%%
											  ,%%%%'   .%%%%'              ,%%%%%'             `SSs%%'
											,%%%%'    .%%%'              ,%%%%'                ,%%%'
										  ,%%%%'     .%%%              ,%%%%'                 ,%%%'
										,%%%%'      .%%%'            ,%%%%'                  ,%%%'
									  ,%%%%'        %%%%           ,%%%'                    ,%%%%
									  %%%%'       .:::::         ,%%%'                      %%%%'
									.:::::        :::::'       ,%%%'                       ,%%%%
									:::::'                   ,%%%%'                        %%%%%
															%%%%%'                         %%%%%
														  .::::::                        .::::::
														  ::::::'                        ::::::'   Susie Oviatt

								   */

								   /*
										  _==/          i     i          \==_
										/XX/            |\___/|            \XX\
									  /XXXX\            |XXXXX|            /XXXX\
									 |XXXXXX\_         _XXXXXXX_         _/XXXXXX|
									XXXXXXXXXXXxxxxxxxXXXXXXXXXXXxxxxxxxXXXXXXXXXXX
								   |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
								   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
								   |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
									XXXXXX/^^^^"\XXXXXXXXXXXXXXXXXXXXX/^^^^^\XXXXXX
									 |XXX|       \XXX/^^\XXXXX/^^\XXX/       |XXX|
									   \XX\       \X/    \XXX/    \X/       /XX/
										  "\       "      \X/      "       /"

								   */

