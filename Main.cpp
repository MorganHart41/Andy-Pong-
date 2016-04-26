//All Of The Includes Needed
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>

//All Of The Needed Usings
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::ios;

int main() //This Is Where Things Get Done
{
	//INDEX/INCREMENT TOOLS:
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	string lString; //String Version Of l
	int m = 0;
	string mString; //String Version Of m
	int n = 0;
	int BallValue = 1;

	//Create The Window:
	sf::RenderWindow window(sf::VideoMode(500, 500), "Mad Pong Skills"); 
	window.setFramerateLimit(100); //How Many Frames Allowed



	//Create The PongBall(Size,Color,Position):
	sf::CircleShape PongBall(10); //Creation/Size(Radius)
	sf::Texture AndysFace; //Make A Texture That Holds Andys Face
	if (!AndysFace.loadFromFile("smallface.jpg")) //Used To Import Font Type
	{
		//Checks If It Was Loaded Corrctly And If Not It Does Nothin
	}
	AndysFace.setSmooth(true); //Reduces The Pixelation Image, AKA Makes it Smooth
	//PongBall.setFillColor(sf::Color::Red); //Fills Color
	PongBall.setPosition(250, 250); //Determines Position
	PongBall.setTexture(&AndysFace,true); //Sets The Texture On PongBall To Andys Face
	bool Direction = false; //False For Down, True For Up, This Is The Direction Of The Ball In The Vertical Direction

	sf::RectangleShape Space(sf::Vector2f(500, 500)); //Creation/Size(X,Y)
	Space.setPosition(0, 0); //Determines Position(X,Y)
	sf::Texture Background;
	if (!Background.loadFromFile("space.jpg"))
	{

	}
	Background.setSmooth(true);
	Space.setTexture(&Background, true);



	//Create Left Paddle(Size,Color,Position,PaddleContact):
	sf::RectangleShape LeftPaddle(sf::Vector2f(10, 40)); //Creation/Size(X,Y)
	LeftPaddle.setFillColor(sf::Color::Cyan); //Fills Color
	LeftPaddle.setPosition(5, 50); //Determines Position(X,Y)
	bool LeftPaddleContact = false; //Determines Paddle Contact (Initially False)

	//Create Right Paddle(Size,Color,Position,PaddleContact):
	sf::RectangleShape RightPaddle(sf::Vector2f(10, 40)); //Creation/Size(X,Y)
	RightPaddle.setFillColor(sf::Color::Cyan); //Fills COlor
	RightPaddle.setPosition(485, 50); //Determines Position(X,Y)
	bool RightPaddleContact = false; //Determines Paddle Contact (Initially False)

	//This Section Is Used For Setting Up Font As Well As Creating All The Objects It Will Be Used On
	sf::Font OldNewsPaper; //Creating A Font
	sf::Text LeftWordScore; //Creating The Object That Will Say "Score:" On The Left Side
	sf::Text LeftScore; //The Number That Will Occur After The Word Score On The Left Side
	sf::Text RightWordScore; //Creating The Object That Will Say "Score:" On The Right Side
	sf::Text RightScore; //The Number That Will Occur After The Word Score On The Right Side
	if (!OldNewsPaper.loadFromFile("OldNewspaperTypes.ttf")) //Used To Import Font Type
	{
		//Checks If It Was Loaded Corrctly And If Not It Does Nothin
	}

	//Setting Up The Word "Score:" That Resides On The Left Side
	LeftWordScore.setFont(OldNewsPaper); //Sets Font
	LeftWordScore.setColor(sf::Color::Cyan); //Sets The Color
	LeftWordScore.setString("Score: "); //Sets The String Equal To "Score:" (LEft Side)
	LeftWordScore.setPosition(sf::Vector2f(10,0)); //Sets Position, In This Case On The Left Side

	//Setting Up The Word "Score:" That Resides On The Right Side
	RightWordScore.setFont(OldNewsPaper); //Sets Font
	RightWordScore.setColor(sf::Color::Cyan); //Sets The COlor
	RightWordScore.setString("Score: "); //Sets The String Equal To "Score:" (Right Side)
	RightWordScore.setPosition(sf::Vector2f(380, 0)); //Sets Position, In This Case On The Right Side

	sf::SoundBuffer AndysLaughBuffer; //Needed This, Is Chill
	if (!AndysLaughBuffer.loadFromFile("andy_laughter.wav"))
	{
		//Checks If It Was Loaded Corrctly And If Not It Does Nothin
	}
	sf::Sound AndysLaugh; //Creating The Sound For Andys Laugh
	AndysLaugh.setBuffer(AndysLaughBuffer);

	while (window.isOpen()) //Will Do Everything In Here While The Window Remains Open
	{
		sf::Event event; //Creates An Event

		while (window.pollEvent(event)) //While Events Are Happening Or Something Is Happening
		{
			if (event.type == sf::Event::Closed) //If The Event Is Closed
			{
				window.close(); //Close The Window
			}
			if (event.type == sf::Event::KeyPressed) //If A Key Is Pressed
			{
				if (event.key.code == sf::Keyboard::W) //Button Used To Move Left Paddle Up
				{
					if (LeftPaddle.getPosition().y <= 0) //Makes Sure Left Paddle Cannot Exceed The Top Of The Window
					{
						break;
					}
					LeftPaddle.setPosition(5, 50 + (--i*6)); //Sets New Left Paddle Position
				}
				if (event.key.code == sf::Keyboard::S) //Button Used To Move Left Paddle Down
				{
					if (LeftPaddle.getPosition().y >= 460) //Makes Sure Left Paddle Cannot Exceed The Bottom Of The Window
					{
						break;
					}
					LeftPaddle.setPosition(5, 50 + (++i*6)); //Sets New Left Paddle Position
				}
				if (event.key.code == sf::Keyboard::P) //Button Used To Move Right Paddle Up
				{
					if (RightPaddle.getPosition().y <= 0) //Makes Sure Right Paddle Cannot Exceed The Top Of The Window
					{
						break;
					}
					RightPaddle.setPosition(485, 50 + (--j*6)); //Sets New Right Paddle Position
				}
				if (event.key.code == sf::Keyboard::L) //Button Use To Move Right Paddle DOwn
				{
					if (RightPaddle.getPosition().y >= 460) //Makes Sure Right Paddle Cannot Exceed The Bottom Of The Window
					{
						break;
					}
					RightPaddle.setPosition(485, 50 + (++j*6)); //Set New RIght Paddle Position
				}
			}
		}
		window.clear(); //Clears Window (IDK If This Is Necessary, Too Lazy To CHeck)

		
		//This Next Part Checks If The Ball Hit The Paddles And If So Changes The Contact Values To True Or False When Appropriate
		//The Actual Check Behind If PongBall Hit The Left Paddle
		if (PongBall.getPosition().x == LeftPaddle.getPosition().x+10 && PongBall.getPosition().y >= LeftPaddle.getPosition().y-20 && PongBall.getPosition().y <= LeftPaddle.getPosition().y+40)
		{
			LeftPaddleContact = true; //Hit Left
			RightPaddleContact = false; //Did Not Hit Right
			//The Following If Else Statement Makes The Ball Bounce Off Of The Left Paddle Organically
			if (Direction == true) //Going Up
			{
				Direction == false; //Makes It Go Down
			}
			else //Going Down
			{
				Direction == true; //Makes It Go Up
			}
			LeftPaddle.setFillColor(sf::Color::Cyan); //Fills Color To Inform User They Lost
		}
		//The Actual Check Behind If PongBall Hit The Right Paddle
		if (PongBall.getPosition().x+20 == RightPaddle.getPosition().x && PongBall.getPosition().y >= RightPaddle.getPosition().y-20 && PongBall.getPosition().y <= RightPaddle.getPosition().y + 40)
		{
			RightPaddleContact = true; //Hit Right
			LeftPaddleContact = false; //Did Not Hit Left
			//The Following If Else Statement Makes The Ball Bounce Off Of The Right Paddle Organically
			if (Direction == true) //Going Up
			{
				Direction == false; //Makes It Go Down
			}
			else //Going Down
			{
				Direction == true; //Makes It Go Up
			}
			RightPaddle.setFillColor(sf::Color::Cyan); //Fills Color To Inform User They Lost
		}
		
		//This Part Means That The Ball Hit The Wall And Must Rebound
		if (PongBall.getPosition().y == 0) //PongBall Hit The Top Of The Window
		{
			Direction = true;
		}
		if (PongBall.getPosition().y == 480) //PongBall Hit The Bottom Of The Window
		{
			Direction = false;
		}


		//This Section Uses The Values Of PaddleContact In Order To Determine Which Direction The Ball Will Be Going
		if (LeftPaddleContact == false && Direction == true) //Will Check If The Left Paddle Missed The PongBall
		{
			PongBall.setPosition(PongBall.getPosition().x - 1, PongBall.getPosition().y + 1); //Since It Missed The Ball Will Keep Going Left
		}
		if (LeftPaddleContact == true && Direction == true) //Will Check If The Left Paddle Hit The PongBall
		{
			PongBall.setPosition(PongBall.getPosition().x + 1, PongBall.getPosition().y + 1); //Since It Hit The Ball It Will Change The Balls Direction To The Right
		}
		if (LeftPaddleContact == false && Direction == false) //Will Check If The Left Paddle Missed The PongBall
		{
			PongBall.setPosition(PongBall.getPosition().x - 1, PongBall.getPosition().y - 1); //Since It Missed The Ball Will Keep Going Left
		}
		if (LeftPaddleContact == true && Direction == false) //Will Check If The Left Paddle Hit The PongBall
		{
			PongBall.setPosition(PongBall.getPosition().x + 1, PongBall.getPosition().y - 1); //Since It Hit The Ball It Will Change The Balls Direction To The Right
		}
		if (RightPaddleContact == true && LeftPaddleContact == true) //If The Right Paddle Returned The Ball It Is Then Up To The Left Paddle To Return It
		{
			LeftPaddleContact = false; //I Did This Because It Works
		}


		//Checks If Either Of The Users Had Lost (Visually Tells Them)
		if (PongBall.getPosition().x == -10) //Determines If The Left User Lost
		{
			LeftPaddle.setFillColor(sf::Color::Red); //Fills Color To Inform User They Lost
			m++;//Increment In Order To Track Score
			PongBall.setPosition(250, 250); //Sets The Balls Position Back To Default In Order To Start Over
			RightPaddle.setFillColor(sf::Color::Cyan); //Color Indication In Order To Signal You Lost
			AndysLaugh.play();
		}
		if (PongBall.getPosition().x == 500) //Determines If The Right User Lost
		{
			RightPaddle.setFillColor(sf::Color::Red); //Fills Color To Inform User They Lost
			l++; //Increment In Order To Track Score
			PongBall.setPosition(250, 250); //Sets The Balls Position Back To Default In Order To Start Over
			LeftPaddle.setFillColor(sf::Color::Cyan); //Color Indication In Order To Signal You Lost
			AndysLaugh.play();
		}

		//This Section Is Where I Pass The Number As Well As Position For The Score (Left Side)
		LeftScore.setFont(OldNewsPaper); //Sets The Font
		LeftScore.setColor(sf::Color::Cyan); //Sets The Color
		lString = std::to_string(l); //This Line Changes The Integer To A String, Required For The Next Line Because It Only Takes A String
		LeftScore.setString(lString); //Sets The String Passed Equal To Left Score
		LeftScore.setPosition(sf::Vector2f(100, 0)); //Sets The Left Strings Position

		//This Section Is Where I Pass The Number As Well As Position For The Score (Right Side)
		RightScore.setFont(OldNewsPaper); //Sets The Font
		RightScore.setColor(sf::Color::Cyan); //Sets The Color
		mString = std::to_string(m); //This Line CHanges The Integer To A String, Required For The Next Line Because It Only Takes A String
		RightScore.setString(mString); //Sets The String Passed Equal To Right Score
		RightScore.setPosition(sf::Vector2f(470, 0)); //Sets The Right Strings Position


		//Draws Everything That Has Been Changed To The Screen
		window.draw(Space);
		window.draw(PongBall); //Draws PongBall
		window.draw(LeftPaddle); //Draws The Left Paddle
		window.draw(RightPaddle); //Draws The Rifht Paddle
		window.draw(LeftWordScore); //Draws The Word Score On The Left Side
		window.draw(LeftScore); //Draws The Actual Number For Left Paddles Score
		window.draw(RightWordScore); //Draws The Word Score On The Left Side
		window.draw(RightScore); //Draws The Actual Number For Right Paddles Score
		window.display(); //Displays It All
	}
	return 0; //Required Seeing As We Are In Main
}