#include <iostream>
using namespace std;

struct Position {
    int x = 0;
    int y = 0;

    void setValues(int xPos, int yPos) {
        x = xPos;
        y = yPos;
    }                   

    // make a getter if you want
};

// Should it be a abstract class?
class GameObject 
{
    protected:
            Position position;
    public:

        GameObject(int x=0,int y=0)
        {
            position.setValues(x,y);
        }

        void setValues(int x,int y)
        {
            position.setValues(x,y);
        }

        int getx()
        {
            return position.x;
        }

        int gety()
        {
            return position.y;
        }

        //        ---------child classes override them---------------
        
        virtual void display()
        {
            cout<<" . ";
        }

        virtual char getchar()
        {
            return '.';
        }
        
};




class PlayerCar:public GameObject{

    private:
        char ch;
    public:
        PlayerCar(int x=0,int y=0,char ch='C'): GameObject(x,y)
        {
            this->ch=ch;
        }

        void display()override
        {
            cout<<" "<<ch<<" ";
        }

        char getchar()override
        {
            return ch;
        }
};

class FuelStations:public GameObject{

    private:
        char ch;

    public:
        FuelStations(int x=0,int y=0,char ch='F'): GameObject(x,y), ch(ch){}

        void display()override
        {
            cout<<" "<<ch<<" ";
        }

        char getchar()override
        {
            return ch;
        }
};

class Obstacle:public GameObject
{
    public:

    Obstacle(int x=0,int y=0) : GameObject(x,y){} 

    virtual void display()
    {
        cout<<"no used";
    }

    virtual char getchar()
    {
        return '.';
    }
};


class Trees:public Obstacle
{
    private:

        char ch;

    public:
        Trees(int x=0,int y=0,char ch ='T') : Obstacle(x,y), ch(ch){}
        
        void display()override
        {
            cout<<" "<<ch<<" ";
        }

        char getchar()
        {
            return ch;
        }
};


class OtherCars:public Obstacle{
    private:
        char ch;

    public:
        OtherCars(int x=0,int y=0,char other='O'):ch(other),Obstacle(x,y){}

        void display()override
        {
            cout<<" "<<ch<<" ";
        }

        char getchar()
        {
            return ch;
        }
};


class Building: public Obstacle{

    private:
        char ch;
    
    public:
        Building(int x=0,int y=0,char ch='B'):ch(ch),Obstacle(x,y){}

        void display()override
        {
            cout<<" "<<ch<<" ";
        }

        char getchar()
        {
            return ch;
        }
};

//==========================================================================



class Game {

    private:

        int numRows, numCols;
        GameObject*** grid; // why 3d? Understand it by yourself
        GameObject *carpos;
        Position buildings[5][21]; 
        Position trees[7];
        Position otherCars[4];
        Position fuelStations[4];
        Position playerCarPosition;
    
    public:
        Game(int r, int c) : numRows(r), numCols(c) {
		grid=new GameObject** [r];
            for(int i=0;i<r;i++){
            	grid[i]=new GameObject*[c];
            }
            
            setBuildingIndexes();                 // indexes wher building cells
            setTreeIndexes();                    // indexes where trees
            setOtherCarsIndexes();              // indexes where other cars
            setFuelStationIndexes();           // indexes where ch stations
            playerCarPosition.setValues(1,1); // indexes where player ch

            for(int i=0;i<numRows;i++)
            {
            	for(int j=0;j<numCols;j++)
                {
            		bool cond=false;
            		for(int a=0;a<7;a++) 
            		if(i==trees[a].x&& j==trees[a].y)
                    {
            				GameObject *ch =new Trees(i,j);
            				grid[i][j]=ch;
                            cond=true;
            		}


            		for(int a=0;a<4;a++) 
            		if(i==otherCars[a].x && j==otherCars[a].y)
                    {
            				GameObject *caar=new OtherCars(otherCars[a].x,otherCars[a].y);
            				grid[i][j]=caar;
                            cond=true;
            		}
                    
            		for(int a=0;a<4;a++) 
            		if(i==fuelStations[a].x && j==fuelStations[a].y)
                    {
            				GameObject *ffuel=new FuelStations(fuelStations[a].x,fuelStations[a].y);
            				grid[i][j]=ffuel;
                            cond=true;
            		}

            		if(i==playerCarPosition.x && j==playerCarPosition.y)
                    {
            				GameObject *pp=new PlayerCar(playerCarPosition.x,playerCarPosition.y);
            				grid[i][j]=pp;
                            cond=true;
                            carpos=pp;
            		}

            		for(int b=0;b<5;b++)
            		for(int a=0;a<21;a++) 
            		if(i==buildings[b][a].x && j==buildings[b][a].y)
                    {
            				GameObject *bb=new Building(buildings[b][a].x,buildings[b][a].y);
            				grid[i][j]=bb;cond=true;
            		}

            		if(!cond)
                    {
                        grid[i][j]=new GameObject(i,j);
                    }
            	}
            }
            
        }


        void moveleft()
        {
            int x = carpos->getx();
            int y = carpos->gety();
           
            if (y > 0) 
            {
                char temp=grid[x][y-1]->getchar();
                if(temp=='T'||temp=='B'||temp=='O'||temp=='F'){
                    cout<<"Collision\n";
                    return;
                }
                grid[x][y] = new GameObject(x, y); 
                carpos->setValues(x, y-1);
                grid[x][y-1] = carpos;
            }
            
        }
        
        void moveright()
        {
            int x = carpos->getx();
            int y = carpos->gety();
           
            if (y < numRows - 1) {
                char temp=grid[x][y+1]->getchar();
                if(temp=='T'||temp=='B'||temp=='O'||temp=='F')
                {
                    cout<<"collision\n";
                    return;
                }
           
                grid[x][y] = new GameObject(x, y);
                carpos->setValues(x, y+1);
                grid[x ][y+1] = carpos;
            }
        }
        
        void moveup()
        {
            int x = carpos->getx();
            int y = carpos->gety();
           
            if (x > 0) 
            {
                char temp=grid[x-1][y]->getchar();

                if(temp=='T'||temp=='B'||temp=='O'||temp=='F')
                {
                    cout<<"collision\n";
                    return;
                }

                grid[x][y] = new GameObject(x, y);
                carpos->setValues(x-1, y );
                grid[x-1][y] = carpos;
            }
        }
        
        void movedown()
        {
            int x = carpos->getx();
            int y = carpos->gety();
           
            if (x < numCols-1) 
            {
                char temp=grid[x+1][y]->getchar();

                if(temp=='T'||temp=='B'||temp=='O'||temp=='F')
                {
                    cout<<"Collision\n";
                    return;
                }

                grid[x][y] = new GameObject(x, y);

                carpos->setValues(x+1, y );

                grid[x+1][y] = carpos;

            }
        }
        
    	void checkmovement()
        {
            char key='r';

            do
            {
                
                cout<<"enter key [enter z to quit game] :";
                cin>>key;

                system("clear");

                if(key=='d')
                {
                    moveleft();
                }
                
                else if(key=='w')
                {
                    movedown();
                }
                
                else if (key=='a')
                {
                    moveright();
                }

                else if(key =='s')
                {
                    moveup();
                }

                displayGrid();

            }
            while(key!='z');

        }


        void displayGrid() 
        {
           
            for (int i = 0; i < numRows; i++) 
            {
                for (int j = 0; j < numCols; j++) 
                {
                    grid[i][j]->display();
                }

                cout << endl;
            }
        }

        void setBuildingIndexes() 
        {

            int startX = 5;
            int startY = 5;
            for (int i = 0; i < 5; i++) 
            {

                int x = startX;
                int y = startY;
                for (int j = 0; j<21; j++) {
                    buildings[i][j].setValues(x,y);
                    y++;

                    if ((j+1) % 7 == 0) {
                        y = startY;
                        x+=1;
                    }
                }

                startX+=5; 
                startY+=8;

                if (i==2) {
                    startY = 1;
                }
            }
        
        }

        void setTreeIndexes(){
            trees[0].setValues(2, 20);
            trees[1].setValues(25, 20);
            trees[2].setValues(15, 2);
            trees[3].setValues(18, 17);
            trees[4].setValues(3, 3);
            trees[5].setValues(8, 18);
            trees[6].setValues(28, 2);
           
        }

        void setOtherCarsIndexes(){
            otherCars[0].setValues(12, 27);
            otherCars[1].setValues(25, 27);
            otherCars[2].setValues(15, 10);
            otherCars[3].setValues(20, 13);
        }

        void setFuelStationIndexes(){
            fuelStations[0].setValues(2, 27);
            fuelStations[1].setValues(20, 15);
            fuelStations[2].setValues(28, 19);
            fuelStations[3].setValues(25, 6);
        }


    };

    int main() {
        Game game(30, 30);  
        game.displayGrid();
        game.checkmovement();
        return 0;
    }
