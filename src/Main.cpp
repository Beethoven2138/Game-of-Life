/*    This file is part of Game of Life.

    Game of Life is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Game of Life is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Game of Life.  If not, see <http://www.gnu.org/licenses/>.
*/

//Author: Saxon Supple

#include <iostream>
#include <SFML/Graphics.hpp>

#define boardWidth 50
#define boardHeight 50
#define blockLength 10
#define scale 1

sf::RenderWindow window(sf::VideoMode(1* blockLength * boardWidth, 1 * blockLength * boardHeight), "Game of Life");

float timeBetweenMoves = 1;

bool board[boardHeight][boardWidth];

sf::RectangleShape rects[boardWidth][boardHeight];

int NumOfNeighbours(int xPos, int yPos);

void UpdateRects();

void ChangeBoard();

void InitRects();

void MousePressed();

bool startGame = false;

int main(int argc, char *argv[])
{

  
  
  sf::Clock clock;

  InitRects();

  UpdateRects();

  
  while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
	  switch(event.type){
	  case sf::Event::Closed:
	    window.close();
	    break;
	  case sf::Event::KeyPressed:
	    if (event.key.code == sf::Keyboard::Escape)window.close();
	    if (event.key.code == sf::Keyboard::Space)startGame = true;
	    break;
	  default:
	    break;
	  }

	  if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	    MousePressed();
        }

      if(clock.getElapsedTime().asSeconds() >= timeBetweenMoves && startGame){
	ChangeBoard();
	clock.restart();
      }

      window.clear();

      UpdateRects();

      for (int y = 0; y < boardHeight; y++)
	{
	  for (int x = 0; x < boardWidth; x++)
	    {
	      window.draw(rects[x][y]);
	    }
	}
      window.display();
    }
  
  return 0;
}

int NumOfNeighbours(int xPos, int yPos){
  int numOfNeighbours = 0;
  for (int y = -1; y <= 1; y++)
    {
      for (int x = -1; x <= 1; x++)
	{
	  if((x != 0 || y != 0) && x + xPos < boardWidth && x + xPos >= 0 &&
	     y + yPos < boardHeight && y + yPos >= 0){
	    if(board[x + xPos][y + yPos] == 1)
	      numOfNeighbours++;
	  }
	}
    }
  return numOfNeighbours;
}

void ChangeBoard(){

  int numOfNeighbours = 0;

  bool tempArray[boardWidth][boardHeight];

    for (int y = 0; y < boardHeight; y++)
    {
      for (int x = 0; x < boardWidth; x++)
	{
	  tempArray[x][y] = board[x][y];
	}
    }
  
  for (int y = 0; y < boardHeight; y++)
    {
      for (int x = 0; x < boardWidth; x++)
	{
	  numOfNeighbours = NumOfNeighbours(x, y);
	  if(board[x][y] == 1 && numOfNeighbours < 2){
	    tempArray[x][y] = 0;
	  }
	  else if(board[x][y] == 1 && numOfNeighbours > 3)
	    tempArray[x][y] = 0;
	  else if(board[x][y] == 0 && numOfNeighbours == 3)
	    tempArray[x][y] = 1;
	}
    }

    for (int y = 0; y < boardHeight; y++)
    {
      for (int x = 0; x < boardWidth; x++)
	{
	  board[x][y] = tempArray[x][y];
	}
    }
  
  UpdateRects();
}

void InitRects(){
    for (int y = 0; y < boardHeight; y++)
    {
      for (int x = 0; x < boardWidth; x++)
	{
	  rects[x][y].setSize(sf::Vector2f(blockLength * scale, blockLength * scale));
	  rects[x][y].setPosition(x*blockLength * scale, y*blockLength * scale);
	  rects[x][y].setFillColor(sf::Color::White);
	  rects[x][y].setOutlineThickness(1 * scale);
	  rects[x][y].setOutlineColor(sf::Color::Black);
	}
    }
}

void UpdateRects(){
  for (int y = 0; y < boardHeight; y++)
    {
      for (int x = 0; x < boardWidth; x++)
	{
	  if(board[x][y] == 1)
	    rects[x][y].setFillColor(sf::Color::Red);
	  else
	    rects[x][y].setFillColor(sf::Color::White);
	}
    }
}

void MousePressed(){
  int xPos = sf::Mouse::getPosition(window).x;
  int yPos = sf::Mouse::getPosition(window).y;

  xPos = (int) xPos / blockLength;
  yPos = (int) yPos / blockLength;

  board[xPos][yPos] = 1;
}
