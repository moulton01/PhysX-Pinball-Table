#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>


//Static bools used to detect contact between actors. 
static bool deleteObject = false; 
static bool rightBumperHit = false; 
static bool leftBumperHit = false; 
static bool bottomBumperHit = false; 
static bool leftRampHit = false; 
static bool rightRampHit = false; 
static bool updateScore = false; 

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	//Vertices for pinball table. 
	static PxVec3 pinballTable_verts[] = { PxVec3(-20.f, 0.0f, 0.0f), PxVec3(0.0f, 0.0f, 0.0f), PxVec3(0.f, 3.5f, 0.0f), PxVec3(-20.f, 3.5f, 0.0f),//Outside box
		PxVec3(-20.f, 0.0f, -40.0f), PxVec3(0.0f, 0.0f, -40.0f), PxVec3(0.0f, 3.5f, -40.0f), PxVec3(-20.f, 3.5f, -40.0f),//Outside box

		PxVec3(-19.8f, 0.0f, -0.2f), PxVec3(-0.2f, 0.0f, -0.2f), PxVec3(-0.2f, 3.5f, -0.2f), PxVec3(-19.8f, 3.5f, -0.2f),//Inside box
		PxVec3(-19.8f, 0.0f, -39.8f), PxVec3(-0.2f, 0.0f, -39.8f), PxVec3(-0.2f, 3.5f, -39.8f), PxVec3(-19.8f, 3.5f, -39.8f) };//Inside box

	//Triganometry for pinball table.
	static PxU32 pinballTable_trigs[] = { 1, 2, 0, 2, 3, 0, 5, 6, 4, 6, 7, 4, 1, 5, 0, 5, 4, 0, 5, 1, 2, 6, 5, 2, 4, 0, 3, 7, 4, 3,//Box 1
		9, 8, 11, 10, 9, 11, 13, 14, 12, 14, 15, 12, 9, 13, 8, 13, 12, 8, 13, 9, 10, 14, 13, 10, 11, 8, 12, 12, 15, 11,//Box 2
		2, 10, 3, 10, 11, 3, 7, 15, 6, 15, 14, 6, 6, 14, 2, 14, 10, 2, 3, 11, 7, 11, 15, 7 };//Fills gaps between the boxes.

	//Pinball table Class
	class pinballTable : public TriangleMesh
	{
	public:
		pinballTable(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pinballTable_verts), end(pinballTable_verts)), vector<PxU32>(begin(pinballTable_trigs), end(pinballTable_trigs)), pose)
		{
		}
	};

	//Triganometry and vertices for the table corners. 
	static PxVec3 Corner_Verts[] = {PxVec3(0.0,0.0,0.0), PxVec3(0.0, 2.0, 0.0), PxVec3(5.0, 0.0, 0.0), PxVec3(5.0, 2.0, 0.0),PxVec3(0.0, 0.0, 5.0), PxVec3(0.0, 2.0, 5.0)};
	static PxU32 Corner_trigs[] = {5,4,2,3,5,2,1,0,5,4,5,0,0,1,2,3,2,1,3,1,5,2,0,4}; 

	//static Corner object class. 
	class BoardCorner : public TriangleMesh
	{
		public:
		BoardCorner(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(Corner_Verts), end(Corner_Verts)), vector<PxU32>(begin(Corner_trigs), end(Corner_trigs)), pose)
		{
		}
	};

	//Triganometry and Vertices for the static object coving the plunger.
	static PxVec3 PlungerCover_Verts[] = {PxVec3(0.0,0.0,0.0)/*0*/, PxVec3(0.0,0.0,0.3)/*1*/,PxVec3(26.5,0.0,0.3)/*2*/,PxVec3(26.5,0.0,0.0)/*3*/,PxVec3(0.0,1.2,0.0)/*4*/,PxVec3(0.0,1.2,0.3)/*5*/,PxVec3(0.0,1.4,0.0)/*6*/, PxVec3(0.0,1.2,0.4)/*7*/,PxVec3(0.0,1.4,0.4)/*8*/,PxVec3(26.5,1.2,0.4)/*9*/,PxVec3(26.5,1.2,0.3)/*10*/,PxVec3(26.5,1.4,0.4)/*11*/,PxVec3(26.5,1.2,0.0)/*12*/, PxVec3(26.5,1.4,0.0)/*13*/};
	static PxU32 PlungerCover_trigs[] = {3,0,1,
										1,2,3,
										10,5,1,
										1,2,10,
										0,3,13,
										13,6,0,
										13,6,8,
										8,11,13,
										11,8,7,
										7,9,11,
										5,7,9,
										9,10,5,
										1,5,4,
										4,0,1,
										6,7,8,
										6,4,7,
										2,3,12,
										12,10,2,
										11,9,12,
										12,13,11}; 

	//PlungerCover class, creating the shoot for plunger. 
	class PlungerCover : public TriangleMesh
	{
	public: 
		PlungerCover(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(PlungerCover_Verts), end(PlungerCover_Verts)), vector<PxU32>(begin(PlungerCover_trigs), end(PlungerCover_trigs)), pose)
		{
		}
	};

	//Triganometry and vertices for the bumper covering the pinball shoot. 
	static PxVec3 CoverBumper_Verts[] = {PxVec3(0.0, 0.0, 0.0), PxVec3(0.2, 0.0, 0.0), PxVec3(0.0,0.0,-22.0),PxVec3(0.2, 0.0, -22.0), PxVec3(0.0, 1.2, 0.0), PxVec3(0.2, 1.2, 0.0), PxVec3(0.0,1.2,-22.0),PxVec3(0.2, 1.2, -22.0)};
	static PxU32 CoverBumper_trigs[] = {5,4,0,0,1,5,6,4,5,5,7,6,3,2,0,0,1,3,0,2,6,6,4,0,6,7,3,3,2,6,3,7,5,5,1,3}; 
	
	//Class for pinball shoot bumper. 
	class CoverBumper : public TriangleMesh
	{
	public:
		CoverBumper(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(CoverBumper_Verts), end(CoverBumper_Verts)), vector<PxU32>(begin(CoverBumper_trigs), end(CoverBumper_trigs)), pose)
			{
			}
	};

	//Triganometry and vertices for the middle triangle.
	static PxVec3 middleTriangle_Verts[] = {PxVec3(0.0, 0.0, 0.0),PxVec3(6.5, 0.0, 0.0),PxVec3(3.25, 0.0, -1.5),PxVec3(0.0, 1.2, 0.0),PxVec3(6.5, 1.2, 0.0),PxVec3(3.25, 1.2, -1.5)};
	static PxU32 middleTriangle_trigs[] = {4,3,0,0,1,4,4,1,2,2,5,4,3,5,2,2,0,3,5,3,4,1,2,0}; 

	//Middle triangle class. 
	class middleTriangle : public TriangleMesh
	{
	public:
		middleTriangle(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(middleTriangle_Verts), end(middleTriangle_Verts)), vector<PxU32>(begin(middleTriangle_trigs), end(middleTriangle_trigs)), pose)
			{
			}
	};

	//Triganometry and vertices for the middle triangle2.
	static PxVec3 middleTriangle2_Verts[] = {PxVec3(0.0, 0.0, -0.1),PxVec3(3.2, 0.0, -1.6),PxVec3(3.2, 0.0, -5.0), PxVec3(0.0,1.2, -0.1),PxVec3(3.2, 1.2, -1.6),PxVec3(3.2, 1.2, -5.0)};
	static PxU32 middleTriangle2_trigs[] = {4,3,0,0,1,4,4,1,2,2,5,4,3,5,2,2,0,3,5,3,4,1,2,0}; 

	//Middle triangle class. 
	class middleTriangle2 : public TriangleMesh
	{
	public:
		middleTriangle2(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(middleTriangle2_Verts), end(middleTriangle2_Verts)), vector<PxU32>(begin(middleTriangle2_trigs), end(middleTriangle2_trigs)), pose)
			{
			}
	};

	//Triganometry and vertices for the middle triangle3.
	static PxVec3 middleTriangle3_Verts[] = {PxVec3(3.3, 0.0, -1.6),PxVec3(6.5, 0.0, -0.1),PxVec3(3.3, 0.0, -5.0),PxVec3(3.3, 1.2, -1.6),PxVec3(6.5, 1.2, -0.1),PxVec3(3.3, 1.2, -5.0)};
	static PxU32 middleTriangle3_trigs[] = {4,3,0,0,1,4,4,1,2,2,5,4,3,5,2,2,0,3,5,3,4,1,2,0}; 

	//Middle triangle class. 
	class middleTriangle3 : public TriangleMesh
	{
	public:
		middleTriangle3(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(middleTriangle3_Verts), end(middleTriangle3_Verts)), vector<PxU32>(begin(middleTriangle3_trigs), end(middleTriangle3_trigs)), pose)
			{
			}
	};



	//Triganometry and vertices for the middle right side bumper. 
	static PxVec3 RightSideBumper_Verts[] = {PxVec3(0.0, 0.0, 0.0), PxVec3(-2.0, 0.0, -4.0), PxVec3(0.0,0.0,-4.0),PxVec3(0.0, 1.0, 0.0), PxVec3(-2.0, 1.0, -4.0), PxVec3(0.0, 1.0,-4.0)};
	static PxU32 RightSideBumper_trigs[] = {2,1,0,5,4,3,0,3,4,4,1,0,2,5,4,4,1,2,2,5,3,3,0,2}; 

	//Class for the middle right side bumper. 
	class RightSideBumper : public TriangleMesh
	{
	public: 
		RightSideBumper(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(RightSideBumper_Verts), end(RightSideBumper_Verts)), vector<PxU32>(begin(RightSideBumper_trigs), end(RightSideBumper_trigs)), pose)
		{
		}

	};
	//Triganometry and vertices for middle left Bumpers. 
	static PxVec3 sideBumper_Verts[] = {PxVec3(-2.0, 0.0, 0.0), PxVec3(0.0, 0.0, -4.0), PxVec3(-2.0,0.0,-4.0),PxVec3(-2.0, 1.0, 0.0), PxVec3(0.0, 1.0, -4.0), PxVec3(-2.0, 1.0,-4.0)};
	static PxU32 sideBumper_trigs[] = {0,1,2,3,4,5,4,3,0,0,1,4,4,5,2,2,1,4,2,5,3,3,0,2}; 
	//Middle left bumper class. 
	class sideBumper : public TriangleMesh
	{
	public: 
		sideBumper(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(sideBumper_Verts), end(sideBumper_Verts)), vector<PxU32>(begin(sideBumper_trigs), end(sideBumper_trigs)), pose)
		{
		}

	};

	//Triganometry and vertices for top middle right side bumper. 
	static PxVec3 TopRightSideBumper_Verts[] = {PxVec3(0.0, 0.0, -8.0), PxVec3(-2.0, 0.0, -4.0), PxVec3(0.0,0.0,-4.0),PxVec3(0.0, 1.0, -8.0), PxVec3(-2.0, 1.0, -4.0), PxVec3(0.0, 1.0,-4.0)};
	static PxU32 TopRightSideBumper_trigs[] = {0,1,2,3,4,5,4,3,0,0,1,4,4,5,2,2,1,4,3,5,2,2,0,3}; 

	//Top middle right side bumper class. 
	class TopRightSideBumper : public TriangleMesh
	{
	public: 
		TopRightSideBumper(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(TopRightSideBumper_Verts), end(TopRightSideBumper_Verts)), vector<PxU32>(begin(TopRightSideBumper_trigs), end(TopRightSideBumper_trigs)), pose)
		{
		}

	};
	//Triganometry and vertices for top middle left side bumper. 
	static PxVec3 TopSideBumper_Verts[] = {PxVec3(-2.0, 0.0, -8.0), PxVec3(0.0, 0.0, -4.0), PxVec3(-2.0,0.0,-4.0),PxVec3(-2.0, 1.0, -8.0), PxVec3(0.0, 1.0, -4.0), PxVec3(-2.0, 1.0,-4.0)};
	static PxU32 TopSideBumper_trigs[] = {2,1,0,5,4,3,0,3,4,4,1,0,2,5,4,4,1,2,3,5,2,2,0,3}; 
	//Top middle left side bumper class. 
	class TopSideBumper : public TriangleMesh
	{
	public: 
		TopSideBumper(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(TopSideBumper_Verts), end(TopSideBumper_Verts)), vector<PxU32>(begin(TopSideBumper_trigs), end(TopSideBumper_trigs)), pose)
		{
		}

	};
	//Triganometry and vertices for the bottom left bumper. 
	static PxVec3 LeftBumper_Verts[] = {PxVec3(0.0, 0.0, 0.0), PxVec3(-1.0, 0.0, -2.5), PxVec3(2.5,0.0,0.0),PxVec3(0.0, 1.2, 0.0), PxVec3(-1.0, 1.2, -2.5), PxVec3(2.5,1.2,0.0)};
	static PxU32 LeftBumper_trigs[] = {2,1,0,5,4,3,0,2,5,5,3,0,4,1,0,0,3,4,4,5,2,2,1,4}; 
	//Class for bottom left bumper.   
	class LeftBumper : public TriangleMesh
	{
	public: 
		LeftBumper(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(LeftBumper_Verts), end(LeftBumper_Verts)), vector<PxU32>(begin(LeftBumper_trigs), end(LeftBumper_trigs)), pose)
		{
		}
	};
	//Triganometry and vertices for the bottom right bumper. 
	static PxVec3 RightBumper_Verts[] = {PxVec3(0.0, 0.0, 0.0), PxVec3(1.0, 0.0, -2.5), PxVec3(-2.5,0.0,0.0),PxVec3(0.0,1.2, 0.0), PxVec3(1.0, 1.2, -2.5), PxVec3(-2.5,1.2,0.0)};
	static PxU32 RightBumper_trigs[] = {0,1,2,3,4,5,5,2,0,0,3,5,0,1,4,4,3,0,2,5,4,4,1,2}; 
	//Class for bottom right bumper. 
	class RightBumper : public TriangleMesh
	{
	public: 
		RightBumper(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(RightBumper_Verts), end(RightBumper_Verts)), vector<PxU32>(begin(RightBumper_trigs), end(RightBumper_trigs)), pose)
		{
		}
	};
	//Triganometry and vertices for ramp 1(left). 
	static PxVec3 Ramp_Verts[] = {PxVec3(0.0, 0.0, 0.0), PxVec3(2.5, 0.0, 0.0), PxVec3(0.0,0.0,-2.5),PxVec3(2.5,0.0, -2.5), PxVec3(0.0,0.2,-2.5),PxVec3(2.5,0.2, -2.5)};
	static PxU32 Ramp_trigs[] = {0,2,3,3,1,0,5,3,2,2,4,5,4,0,1,1,5,4,3,5,1,2,0,4}; 
	//Class for ramp 1 (left). 
	class Ramp : public TriangleMesh
	{
	public: 
		Ramp(PxTransform pose = PxTransform(PxIdentity)):
			TriangleMesh(vector<PxVec3>(begin(Ramp_Verts), end(Ramp_Verts)), vector<PxU32>(begin(Ramp_trigs), end(Ramp_trigs)), pose)
		{
		}
	};

	//Vertecies for Left Flipper
	static PxVec3 leftflipper_verts[] = { PxVec3(0, 0, 0.25), PxVec3(0, 0, -0.25), PxVec3(0.5, 0, 0.5), PxVec3(0.5, 0, -0.5), PxVec3(2.75, 0, 0.125),
		PxVec3(2.75, 0, -0.125), PxVec3(0, 0.5, 0.25), PxVec3(0, 0.5, -0.25), PxVec3(0.5, 0.5, 0.5), PxVec3(0.5, 0.5, -0.5), PxVec3(2.75, 0.5, 0.125), PxVec3(2.75, 0.5, -0.125) };

	//Vertecies for Right Flipper
	static PxVec3 rightflipper_verts[] = { PxVec3(0, 0, 0.25), PxVec3(0, 0, -0.25), PxVec3(-0.5, 0, 0.5), PxVec3(-0.5, 0, -0.5), PxVec3(-2.75, 0, 0.125),
		PxVec3(-2.75, 0, -0.125), PxVec3(0, 0.5, 0.25), PxVec3(0, 0.5, -0.25), PxVec3(-0.5, 0.5, 0.5), PxVec3(-0.5, 0.5, -0.5), PxVec3(-2.75, 0.5, 0.125), PxVec3(-2.75, 0.5, -0.125) };

	//Left Flipper Class
	class LeftFlipper : public ConvexMesh
	{
	public:
		LeftFlipper(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(leftflipper_verts), end(leftflipper_verts)), pose, density)
		{

		}
	};

	//Right Flipper Class
	class RightFlipper : public ConvexMesh
	{
	public:
		RightFlipper(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(rightflipper_verts), end(rightflipper_verts)), pose, density)
		{

		}
	};

	static PxVec3 RightRamp_verts[] = {PxVec3(0.0, 0.0, 0.0), PxVec3(2.51, 0.0, 0.0), PxVec3(0.0,0.0,-2.5),PxVec3(2.51,0.0, -2.5), PxVec3(0.0,0.4,-2.5),PxVec3(2.51,0.4, -2.5)};

	class RightRamp : public ConvexMesh
	{
	public:
		RightRamp(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(RightRamp_verts), end(RightRamp_verts)), pose, density)
		{

		}
	};

	struct FilterGroup
	{
		enum Enum
		{
			PLUNGER		= (1 << 3),
			COVER		= (2 << 3),
			TABLE		= (1 << 0),
			PINBALL     = (1 << 1), 
			LEFTBUMPER	= (3 << 2),
			RIGHTBUMPER = (3 << 2),
			BOTTOMBUMPER= (3 << 2),
			BUMPERCOVER = (1 << 4),
			RAMPLEFT =    (4 << 1),
			RAMPRIGHT   = (4 << 1)
			//add more if you need
		};
	};
	//Class creating the plunger. 
	class Plunger
	{
		//Distance joint for the spring off the plunger. 
		DistanceJoint *Spring; 
		//Box to be used as the actual plunger attached to the spring. 
		Box *PlungerTop;

	public:
		// Sets out Dimentions and properties of the plunger. 
		Plunger(const PxVec3& dimensions=PxVec3(.8f,.8f,.8f), PxReal stiffness=8.0f, PxReal damping=0.1f)
		{
			PxMaterial* plungerMat = CreateMaterial(0.0f,0.0f,1.16f);
			PlungerTop = new Box(PxTransform(PxVec3(-.7f,3.5f,-14.0f)), PxVec3(.5f,.5f,.5f));
			PlungerTop->Material(plungerMat); //Assigns material to plunger. 
			PlungerTop->SetupFiltering(FilterGroup::PLUNGER, FilterGroup::COVER); 
			PxRigidBody* px_actor = (PxRigidBody*)PlungerTop->Get(); 
			px_actor->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD,true); 
			PlungerTop->Color(color_palette[1]);
			PlungerTop->Name("Plunger_Top"); 

			Spring = new DistanceJoint(NULL, PxTransform(PxVec3(-1.0f,1.5f,-.15f)), PlungerTop, PxTransform(PxVec3(0.0f,0.0f,13.f)));

			Spring->Stiffness(stiffness); 
			Spring->Damping(damping); 
		}
		void AddToScene(Scene* scene)
		{
			//scene->Add(PlungerBottom); 
			scene->Add(PlungerTop); 
		}
		~Plunger()
		{
			delete Spring; 
		}

	};
	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;
						deleteObject = true; 
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;
			string contactName = pairHeader.actors[1]->getName();
			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
					if (contactName == "rightBumper")
					{
						rightBumperHit = true; 
						updateScore = true; 
					}
					if (contactName == "leftBumper")
					{
						leftBumperHit = true;
						updateScore = true;
					}
					if (contactName == "bottomBumper")
					{
						bottomBumperHit = true; 
						updateScore = true;
					}
					if (contactName == "leftRamp")
					{
						leftRampHit = true;
						updateScore = true;
					}
					if (contactName == "rightRamp")
					{
						rightRampHit = true;
						updateScore = true;
					}
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		//Pointers to all the different actors and meshes in my scene. 
		Plane* plane;
		MySimulationEventCallback* my_callback;
		pinballTable* table;
		BoardCorner *Corner, *CornerTwo; 
		resetTrigger *resetBoard; 
		LeftFlipper* left_flipper;
		LeftBumper* left_bumper; 
		RightBumper* right_bumper; 
		CoverBumper *cover_bumper;
		middleTriangle *middle_Triangle; 
		middleTriangle2 *middle_Triangle2; 
		middleTriangle3 *middle_Triangle3; 
		sideBumper *side_bumper; 
		RightSideBumper *right_side_bumper; 
		TopSideBumper *top_side_bumper; 
		TopRightSideBumper *top_right_side_bumper; 
		RightFlipper* right_flipper;
		RevoluteJoint* leftflipper_joint;
		RevoluteJoint* rightflipper_joint;
		Plunger* plungerJoint; 
		Sphere* pinball;
		plungerWall* RightWall, CoverWall; 
		Box *resetBox; 
		PlungerCover* Cover;
		RightRamp *bottom_right_ramp;
		Ramp *bottom_left_ramp; 

		
	public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene(&CustomFilterShader) {};

		///A custom scene class
		void SetVisualisation()
		{
			//Visualization parameters. 
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
			
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);

			//Materials for different objects and actors in the scene. 
			PxMaterial* pinballMat = CreateMaterial(0.0f,0.0f,0.597f); 
			PxMaterial* FlipperMat = CreateMaterial(0.0f,0.0f,1.16f);
			

			//The plane below everything. 
			plane = new Plane();
			plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
			Add(plane);
			
			//The pinball table itself. 
			table = new pinballTable(PxTransform(PxVec3(0.f, 0.5f, 0.f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));// Creates table and sets it to 6 degress of tilt.
			table->Name("Table"); //Setting name. 
			table->SetupFiltering(FilterGroup::TABLE, FilterGroup::PINBALL); //Setting up Filter Groups. 
			Add(table); //Adding object to the scene. 

			//The top two corners in the pinball table. 
			Corner = new BoardCorner(PxTransform(PxVec3(-19.8f, 8.0f, -39.1f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));
			Corner->Color(color_palette[1]);
			Add(Corner); 

			CornerTwo = new BoardCorner(PxTransform(PxVec3(-0.2f, 8.0f, -39.1f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))* PxQuat(-50.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))));
			CornerTwo->Color(color_palette[1]);
			Add(CornerTwo); 

			//Left bumper. 
			left_bumper = new LeftBumper(PxTransform(PxVec3(-16.25f, 1.65f, -5.5f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));
			left_bumper->Color(color_palette[1]);
			Add(left_bumper); 

			//right bumper. 
			right_bumper = new RightBumper(PxTransform(PxVec3(-4.75f, 1.65f, -5.5f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));
			right_bumper->Color(color_palette[1]); 
			Add(right_bumper); 


			//ResetBoard to remove actor from scene once the pinball passes into the deadzone. 
			resetBoard = new resetTrigger(PxTransform(PxVec3(-10.5f, 1.5f, -0.5f), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));
			resetBoard->Color(color_palette[2]);
			Add(resetBoard); 
			resetBoard->SetTrigger(1); 

			//Left Flipper. 
			left_flipper = new LeftFlipper(PxTransform(PxVec3(-15.f, 2.5f, -10.f))); //, PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			left_flipper->Color(color_palette[1]);
			left_flipper->Material(FlipperMat); //Assigns material to plunger.
			Add(left_flipper);

			//Right Flipper. 
			right_flipper = new RightFlipper(PxTransform(PxVec3(-15.f, 2.5f, -10.f))); //, PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));
			right_flipper->Color(color_palette[1]);
			right_flipper->Material(FlipperMat);
			Add(right_flipper);

			//The revolute joints for both the flippers. 
			leftflipper_joint = new RevoluteJoint(NULL, PxTransform(PxVec3(-13.5f,1.51f, -5.f), PxQuat(PxPi/2,PxVec3(0.f,0.f,1.f)) *PxQuat(-6.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))), left_flipper, PxTransform(PxVec3(0.25f, 0.f, 0.f),PxQuat(PxPi/2,PxVec3(0.f,0.f,1.f))));
			leftflipper_joint->SetLimits(-0.3f, 0.8f);

			rightflipper_joint = new RevoluteJoint(NULL, PxTransform(PxVec3(-7.5f, 1.51f, -5.f),PxQuat(PxPi/2,PxVec3(0.f,0.f,1.f)) *PxQuat(-6.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))), right_flipper, PxTransform(PxVec3(-0.25f, 0.f, 0.f), PxQuat(PxPi/2,PxVec3(0.f,0.f,1.f))));
			rightflipper_joint->SetLimits(-0.8f, 0.30f);

			//Pluner joint and object.
			plungerJoint = new Plunger();
			plungerJoint->AddToScene(this); 

			//Cover object providing a shoot for the plunger to sit in. 
			Cover = new PlungerCover(PxTransform(PxVec3(-1.6f, 0.8f, -0.15), PxQuat(6.f *(PxPi / 100), PxVec3(1.f, 1.0f, 0.0f)) * PxQuat(44.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))));
			Cover->SetupFiltering(FilterGroup::COVER, FilterGroup::PLUNGER); 
			Cover->Color(color_palette[1]);
			Add(Cover);

			//Bumper covering the pinball shoot. 
			cover_bumper = new CoverBumper(PxTransform(PxVec3(-1.9f, 0.9f, -1.0), PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))));
			cover_bumper->SetupFiltering(FilterGroup::BUMPERCOVER, FilterGroup::PINBALL); 
			cover_bumper->Color(color_palette[1]);
			Add(cover_bumper);

			//Left middle side bumper. 
			side_bumper = new sideBumper(PxTransform(PxVec3(-17.8f, 3.0f, -13.0),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			side_bumper->Color(color_palette[1]);
			Add(side_bumper); 

			//right middle side bumper. 
			right_side_bumper = new RightSideBumper(PxTransform(PxVec3(-2.0f, 3.0f, -13.0),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			right_side_bumper->Color(color_palette[1]);
			Add(right_side_bumper); 

			//Top left side bumper. 
			top_side_bumper = new TopSideBumper(PxTransform(PxVec3(-17.8f, 3.0f, -13.0),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			top_side_bumper->Color(color_palette[1]);
			Add(top_side_bumper); 

			//Top right side bumper.
			top_right_side_bumper = new TopRightSideBumper(PxTransform(PxVec3(-2.0f, 3.0f, -13.0),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			top_right_side_bumper->Color(color_palette[1]);
			Add(top_right_side_bumper);

			//Bottom middle Triangle
			middle_Triangle = new middleTriangle(PxTransform(PxVec3(-13.0f, 5.51f, -25.0),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			middle_Triangle->SetupFiltering(FilterGroup::BOTTOMBUMPER, FilterGroup::PINBALL);
			middle_Triangle->Name("bottomBumper"); 
			middle_Triangle->Color(color_palette[1]);
			Add(middle_Triangle); 

			//Left middle Triangle
			middle_Triangle2 = new middleTriangle2(PxTransform(PxVec3(-13.5f, 5.51f, -25.5),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			middle_Triangle2->Color(color_palette[1]);
			middle_Triangle2->SetupFiltering(FilterGroup::LEFTBUMPER, FilterGroup::PINBALL);
			middle_Triangle2->Name("leftBumper"); 
			Add(middle_Triangle2); 

			//Right middle Triangle
			middle_Triangle3 = new middleTriangle3(PxTransform(PxVec3(-12.5f, 5.51f, -25.5),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f)))); 
			middle_Triangle3->Color(color_palette[1]);
			middle_Triangle3->SetupFiltering(FilterGroup::RIGHTBUMPER, FilterGroup::PINBALL);
			middle_Triangle3->Name("rightBumper"); 
			Add(middle_Triangle3); 

			bottom_left_ramp = new Ramp(PxTransform(PxVec3(-12.0f, 2.80f, -12.0),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))* PxQuat(10.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))));
			bottom_left_ramp->Color(color_palette[1]);
			bottom_left_ramp->Name("leftRamp"); 
			bottom_left_ramp->SetupFiltering(FilterGroup::RAMPLEFT, FilterGroup::PINBALL); 
			Add(bottom_left_ramp); 

			bottom_right_ramp = new RightRamp(PxTransform(PxVec3(-3.0f, 4.89f, -23.0),PxQuat(6.f * (PxPi / 100), PxVec3(1.f, 0.f, 0.f))* PxQuat(-115.f * (PxPi / 100), PxVec3(0.0f, 1.0f, 0.0f))));  
			bottom_right_ramp->SetKinematic(true);
			bottom_right_ramp->Color(color_palette[1]);
			bottom_right_ramp->Name("rightRamp"); 
			bottom_right_ramp->SetupFiltering(FilterGroup::RAMPRIGHT, FilterGroup::PINBALL); 
			Add(bottom_right_ramp);

			//Pinball object. 
			pinball = new Sphere(PxTransform(PxVec3(-0.6f, 5.5f, -19.5f)), PxReal(0.3f));  
			pinball->Name("pinBall"); 
			pinball->SetupFiltering(FilterGroup::PINBALL, FilterGroup::TABLE | FilterGroup::BUMPERCOVER);  // FilterGroup::BUMPER
			pinball->SetupFiltering(FilterGroup::PINBALL, FilterGroup::RIGHTBUMPER);
			pinball->SetupFiltering(FilterGroup::PINBALL, FilterGroup::LEFTBUMPER);
			pinball->SetupFiltering(FilterGroup::PINBALL, FilterGroup::BOTTOMBUMPER);
			pinball->SetupFiltering(FilterGroup::PINBALL, FilterGroup::RAMPLEFT);
			pinball->SetupFiltering(FilterGroup::PINBALL, FilterGroup::RAMPRIGHT);
            PxRigidBody* px_actor1 = (PxRigidBody*)pinball->Get(); //Getting the rigid body of the pinball to set the CCD flag. 
            px_actor1->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true); //Setting CCD to true; 
			pinball->Material(pinballMat); //Assigning the pinball material that was defined earlier to the actual pinball. 
			pinball->Color(color_palette[5]);// changing color. 
			Add(pinball); 
			
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			PxRigidBody* px_actor = (PxRigidBody*)pinball->Get(); 
			//Removes actor when bool deleteObject is true. 
            if (deleteObject == true) {
                px_scene->removeActor(*px_actor);
                deleteObject = false; 
            }
			//applies force to the pinball when rightBumperHit bool is true. 
			if (rightBumperHit == true)
			{
				//PxRigidBody* px_actor = (PxRigidBody*)pinball->Get(); 
				px_actor->addForce(PxVec3(400.0f, 0.0f,-700.0f)); //(ADDS FORCE TO AN ACTOR WHEN COLLIDE).
				rightBumperHit = false;
			}
			//applies force to the pinball when leftBumperHit bool is true. 
			if (leftBumperHit == true)
			{
				//PxRigidBody* px_actor = (PxRigidBody*)pinball->Get(); 
				px_actor->addForce(PxVec3(-400.0f, 0.0f, -700.0f));
				leftBumperHit = false; 
			}
			if (bottomBumperHit == true)
			{
				//PxRigidBody* px_actor = (PxRigidBody*)pinball->Get(); 
				px_actor->addForce(PxVec3(0.0f, -10.0f, 700.0f));
				bottomBumperHit = false; 
			}
			if (rightRampHit == true)
			{
				px_actor->addForce(PxVec3(-400.0f, 0.0f, 400.0f));
				rightRampHit = false;
			}
			if (leftRampHit == true)
			{
				px_actor->addForce(PxVec3(-400.0f, 0.0f, -400.0f));
				leftRampHit = false;
			}

			
		}

		/// An example use of key release handling
		void ExampleKeyReleaseHandler()
		{
			cerr << "I am realeased!" << endl;
		}

		/// An example use of key presse handling
		void ExampleKeyPressHandler()
		{
			cerr << "I am pressed!" << endl;
		}
		//Method called to provide Drive velocity for left flipper. 
		void setLeftVelocityforward()
		{
			((PxRigidDynamic*)left_flipper->Get())->wakeUp();
			leftflipper_joint->DriveVelocity(+10);
		}
		//Method called to provide Drive velocity for left flipper.
		void setLeftVelocitybackward()
		{
			((PxRigidDynamic*)left_flipper->Get())->wakeUp();
			leftflipper_joint->DriveVelocity(-10);
		}
		//Method called to provide Drive velocity for right flipper.
		void setRightVelocityforward()
		{
			((PxRigidDynamic*)right_flipper->Get()) ->wakeUp();
			rightflipper_joint->DriveVelocity(-10);
		}
		//Method called to provide Drive velocity for right flipper.
		void setRightVelocitybackward()
		{
			((PxRigidDynamic*)right_flipper->Get()) ->wakeUp();
			rightflipper_joint->DriveVelocity(+10);
		}
	};
}
