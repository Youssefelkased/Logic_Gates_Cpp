#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string.h>
#include <fstream>
using namespace std;
class Node
{

private:
    std::string Node_name;
    int Node_value;

public:
    Node() : Node_name(""), Node_value(0)
    {
    }
    Node(std::string name, int value) : Node_name(name), Node_value(value)
    {
    }
    Node(std::string name) : Node_name(name), Node_value(0)
    {
    }
    void setname(std::string name)
    {
        Node_name = name;
    }

    void setvalue(int value)
    {
        Node_value = value;
    }

    std::string getname()
    {
        return Node_name;
    }

    int getvalue()
    {
        return Node_value;
    }
    friend std::ostream& operator<<(std::ostream& out, const Node& other){
    		return cout<<other.Node_name<<" "<<other.Node_value;

    	}
};

class Gate
{
protected:
    Node *IN1;
    Node *IN2;
    Node *OUT;
public:
    Gate() : IN1(nullptr), IN2(nullptr), OUT(nullptr)
    {
    }

    ~Gate()
    {
    }


    void set_in1(Node *FirstInput)
    {
        IN1 = FirstInput;
    }

    void set_in2(Node *SecondInput)
    {
        IN2 = SecondInput;
    }

    void set_out(Node *Out)
    {
        OUT = Out;
    }

    Node *get_in1()
    {
        return IN1;
    }

    Node *get_in2()
    {
        return IN2;
    }

    Node *get_out()
    {
        return OUT;
    }
protected:
    virtual void SimulateGate() = 0;
};

/* and */
class AND : public Gate
{
public:
    AND() : Gate()
    {
    }
    void SimulateGate()
    {

        if (IN1->getvalue() == 1 && IN2->getvalue() == 1)
            OUT->setvalue(1);

        else
            OUT->setvalue(0);
    }
};

/* or */
class OR : public Gate
{
public:
    void SimulateGate()
    {

        if (IN1->getvalue() == 0 && IN2->getvalue() == 0)
            OUT->setvalue(0);

        else
            OUT->setvalue(1);
    }
};

/* nand */
class NAND : public Gate
{
public:
    void SimulateGate()
    {
        if (IN1->getvalue() == 1 && IN2->getvalue() == 1)
            OUT->setvalue(0);

        else
            OUT->setvalue(1);
    }
};

/* nor */
class NOR : public Gate
{
public:
    void SimulateGate()
    {
        if (IN1->getvalue() == 0 && IN2->getvalue() == 0)
            OUT->setvalue(1);

        else
            OUT->setvalue(0);
    }
};

/* xor */
class XOR : public Gate
{
public:
    void SimulateGate()
    {
        if (IN1->getvalue() == IN2->getvalue())
            OUT->setvalue(0);

        else
            OUT->setvalue(1);
    }
};

/* xnor */
class XNOR : public Gate
{
public:
    void SimulateGate()
    {
        if (IN1->getvalue() == IN2->getvalue())
            OUT->setvalue(1);

        else
            OUT->setvalue(0);
    }
};

/* not */
class NOT : public Gate
{
public:
    void SimulateGate()
    {
        if (IN1->getvalue() == 1)
            OUT->setvalue(0);

        else
            OUT->setvalue(1);
    }
};

class GateGenerator
{
private:
    Node *Nodes[300];
    Gate *Gates[300];
    int Nodesize;
    int Gatesize;
public:
    GateGenerator()
    {
        int i;
        Gatesize = 0;
        Nodesize = 0;
        for (i = 0; i < GetNode_Size(); i++)
            Nodes[i] = NULL;

        for (i = 0; i < GetGate_Size(); i++)
            Gates[i] = NULL;
    }

    void SetNode_Size(int n)
    {
        Nodesize = n;
    }
    int GetNode_Size()
    {
        return Nodesize;
    }
    void SetGate_Size(int n)
    {
        Gatesize = n;
    }
    int GetGate_Size()
    {
        return Gatesize;
    }
    Node *Create_Node(string n)
    {
        Nodes[Nodesize] = new Node(n);
        Nodesize++;
        return Nodes[Nodesize - 1];
    }

    Node *Find_Node(string n)
    {
        for (int i = 0; i < GetNode_Size(); i++)
        {
            if (n == (Nodes[i]->getname()))
            {
                return Nodes[i];
            }
        }
        return Create_Node(n);
    }

    Gate *Create_Gate(string N)
    {
        Gate *p = NULL;

        if (N == "AND")
            p = new AND();

        else if (N == "NAND")
            p = new NAND();

        else if (N == "OR")
            p = new OR();

        else if (N == "NOR")
            p = new NOR();

        else if (N == "XOR")
            p = new XOR();

        else if (N == "XNOR")
            p = new XNOR();

        else if (N == "NOT")
            p = new NOT();

        else
            return NULL;

        Gatesize++;
        Gates[Gatesize - 1] = p;
        return Gates[Gatesize - 1];
    }

    void startSimulate()
    {
        for (int i = 0; i < GetGate_Size(); i++)
            Gates[i]->SimulateGate();
    }

    void parseInput()
    {

        string out;
        while (1)
        {
            string Nodes;
            cin >> Nodes;

            if (Nodes == "SET")
            {
                string node;
                int mValue;
                cin >> node >> mValue;
                Find_Node(node)->setvalue(mValue);
            }

            else if (Nodes == "OUT")
            {
                string OUT;
                cin >> OUT;
                if (OUT == "ALL")
                {
                    Print_All();
                }
                else
                    cout << Find_Node(OUT)->getname() << ": " << Find_Node(OUT)->getvalue() << endl;
            }

            else if (Nodes == "SIM")
            {
                startSimulate();
            }

            else if (Nodes == "AND" || Nodes == "OR" || Nodes == "NAND" || Nodes == "NOR" || Nodes == "XOR" || Nodes == "XNOR")
            {

                Gate *gate = Create_Gate(Nodes);
                string node1, node2, node3;
                cin >> node1 >> node2 >> node3;
                gate->set_in1(Find_Node(node1));
                gate->set_in2(Find_Node(node2));
                gate->set_out(Find_Node(node3));
            }
            else if (Nodes == "NOT")
            {

                Gate *gate = Create_Gate(Nodes);
                string node1, node2;
                cin >> node1 >> node2;
                gate->set_in1(Find_Node(node1));
                gate->set_out(Find_Node(node2));
            }
            else
            {
                return;
            }
        }
    }
    void Print_All()
    {
        int i;

        for (i = 0; i < GetNode_Size(); i++)
            cout << Nodes[i]->getname()
                 << ": " << Nodes[i]->getvalue() << endl;
    }
};

class Simulator {
private:
	std::vector<Node*> Nodes;
	std::vector<Gate*> Gates;

	int NodeNumber;
	int GateNumber;

public:
	Simulator():Nodes(), Gates(),NodeNumber(0),GateNumber(0) {

	}
	~Simulator();

	Node* CreateNode(std::string nodeName) {

		auto node = new Node(nodeName);
		Nodes.push_back(node);
		NodeNumber++;

		return node;
	}

	Node*  FindNode(std::string nodeName) {

		std::vector<Node*>::iterator found = std::find_if(Nodes.begin(), Nodes.end(), [nodeName](Node* node) {

			return nodeName == node->getname();
			});

		if(found != std::end(Nodes))
			return *found;

		return CreateNode(nodeName);

	}


	Gate*  CreateGate(std::string gateName) {

		Gate* gate = NULL;

		if (gateName == "AND")
			gate = new AND();

		else if (gateName == "NAND")
			gate = new NAND();

		else if (gateName == "OR")
			gate = new OR();

		else if (gateName == "NOR")
			gate = new NOR();

		else if (gateName == "XOR")
			gate = new XOR();

		else if (gateName == "XNOR")
			gate = new XNOR();

		else if (gateName == "NOT")
			gate = new NOT();

		else
			return NULL;


		Gates.push_back(gate);
		GateNumber++;

		return gate;
	}
	void StartSimulation();
	void  PrintAll() {

		for (auto const& node : Nodes)
			std::cout << node->getname()\
			<< ": " << node->getvalue() << "\n";

	}

};

int main()
{
    GateGenerator G1;
    G1.parseInput();
    return 0;
}
