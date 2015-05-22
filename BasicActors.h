#pragma once
    
#include "PhysicsEngine.h"
#include <iostream>
#include <iomanip>
    
namespace PhysicsEngine
{
    ///Plane class
    class Plane : public StaticActor
    {
    public:
        //A plane with default paramters: XZ plane centred at (0,0,0)
        Plane(PxVec3 normal=PxVec3(0.f, 1.f, 0.f), PxReal distance=0.f) 
            : StaticActor(PxTransformFromPlaneEquation(PxPlane(normal, distance)))
        {
            CreateShape(PxPlaneGeometry());
        }
    };
    
    ///Sphere class
    class Sphere : public DynamicActor
    {
    public:
        //a sphere with default parameters:
        // - pose in 0,0,0
        // - dimensions: 1m
        // - denisty: 1kg/m^3
        Sphere(const PxTransform& pose=PxTransform(PxIdentity), PxReal radius=.2f, PxReal density=1.f) 
            : DynamicActor(pose)
        { 
            CreateShape(PxSphereGeometry(radius), density);
        }
    };
    
    ///Box class
    class Box : public DynamicActor
    {
    public:
        //a Box with default parameters:
        // - pose in 0,0,0
        // - dimensions: 1m x 1m x 1m
        // - denisty: 1kg/m^3
        Box(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(.5f,.5f,.5f), PxReal density=1.f) 
            : DynamicActor(pose)
        { 
            CreateShape(PxBoxGeometry(dimensions), density);
        }
    };

	class resetTrigger : public StaticActor
	{
	public:
		resetTrigger(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(8.75f,2.3f,.1f), PxReal density=1.f) 
            : StaticActor(pose)
        { 
            CreateShape(PxBoxGeometry(dimensions), density);
        }
	};
	class plungerWall : public StaticActor
    {
    public:
        plungerWall(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(.05f,1.0f,12.0f), PxReal density=1.f) 
            : StaticActor(pose)
        { 
            CreateShape(PxBoxGeometry(dimensions), density);
        }
    };
    
    class Capsule : public DynamicActor
    {
    public:
        Capsule(const PxTransform& pose=PxTransform(PxIdentity), PxVec2 dimensions=PxVec2(1.f,1.f), PxReal density=1.f) 
            : DynamicActor(pose)
        {
            CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
        }
    };
    
    ///The ConvexMesh class
    class ConvexMesh : public DynamicActor
    {
    public:
        //constructor
        ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose=PxTransform(PxIdentity), PxReal density=1.f)
            : DynamicActor(pose)
        {
            PxConvexMeshDesc mesh_desc;
            mesh_desc.points.count = verts.size();
            mesh_desc.points.stride = sizeof(PxVec3);
            mesh_desc.points.data = &verts.front();
            mesh_desc.flags = PxConvexFlag::eCOMPUTE_CONVEX;
            mesh_desc.vertexLimit = 256;
    
            CreateShape(PxConvexMeshGeometry(CookMesh(mesh_desc)), density);
        }
    
        //mesh cooking (preparation)
        PxConvexMesh* CookMesh(const PxConvexMeshDesc& mesh_desc)
        {
            PxDefaultMemoryOutputStream stream;
    
            if(!GetCooking()->cookConvexMesh(mesh_desc, stream))
                throw new Exception("ConvexMesh::CookMesh, cooking failed.");
    
            PxDefaultMemoryInputData input(stream.getData(), stream.getSize());
    
            return GetPhysics()->createConvexMesh(input);
        }
    };
    
    ///The TriangleMesh class
    class TriangleMesh : public StaticActor
    {
    public:
        //constructor
        TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, const PxTransform& pose=PxTransform(PxIdentity))
            : StaticActor(pose)
        {
            PxTriangleMeshDesc mesh_desc;
            mesh_desc.points.count = verts.size();
            mesh_desc.points.stride = sizeof(PxVec3);
            mesh_desc.points.data = &verts.front();
            mesh_desc.triangles.count = trigs.size();
            mesh_desc.triangles.stride = 3*sizeof(PxU32);
            mesh_desc.triangles.data = &trigs.front();
    
            CreateShape(PxTriangleMeshGeometry(CookMesh(mesh_desc)));
        }
    
        //mesh cooking (preparation)
        PxTriangleMesh* CookMesh(const PxTriangleMeshDesc& mesh_desc)
        {
            PxDefaultMemoryOutputStream stream;
    
            if(!GetCooking()->cookTriangleMesh(mesh_desc, stream))
                throw new Exception("TriangleMesh::CookMesh, cooking failed.");
    
            PxDefaultMemoryInputData input(stream.getData(), stream.getSize());
    
            return GetPhysics()->createTriangleMesh(input);
        }
    };
    class CompoundObject : public DynamicActor
    {
    public:
        CompoundObject(PxTransform pose=PxTransform(PxIdentity),PxQuat rotation = PxQuat(PxIdentity), PxVec2 dimensions=PxVec2(1.f,1.f), PxReal density=1.f) 
            : DynamicActor(pose)
        {
            CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
            CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
            CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
            CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
    
            GetShape(0)->setLocalPose(PxTransform(PxVec3(5.f,0.f,-5.f),PxQuat(1.f,PxVec3(.0f,1.f,.0f))));// PxQuat(1.f,PxVec3(.0f,1.f,.0f))));//sets pose of the first box
            GetShape(1)->setLocalPose(PxTransform(PxVec3(-5.f,0.f,-5.f), PxQuat(-1.f,PxVec3(.0f,1.f,.0f))));//, PxQuat(1.f,PxVec3(1.f,.0f,.0f))));//sets pose of the second box
            GetShape(2)->setLocalPose(PxTransform(PxVec3(5.f,0.f,5.f), PxQuat(-1.f,PxVec3(.0f,1.f,.0f))));//, PxQuat(1.f,PxVec3(.0f,.0f,1.f))));
            GetShape(3)->setLocalPose(PxTransform(PxVec3(-5.f,0.f,5.f),PxQuat(1.f,PxVec3(.0f,1.f,.0f))));
        }
    
    };
    class rectangleEnclosure : public DynamicActor
    {
    public:
        rectangleEnclosure(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) 
            : DynamicActor(pose)
        { 
            CreateShape(PxBoxGeometry(PxVec3(16.f,2.f,1.f)), density);
            CreateShape(PxBoxGeometry(PxVec3(1.f,2.f,16.f)), density);
            CreateShape(PxBoxGeometry(PxVec3(16.f,2.f,1.f)), density);
            CreateShape(PxBoxGeometry(PxVec3(1.f,2.f,16.f)), density);
    
            GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f,0.f,-15.f)));
            GetShape(1)->setLocalPose(PxTransform(PxVec3(-15.f,0.f,0.f)));
            GetShape(2)->setLocalPose(PxTransform(PxVec3(0.f,0.f,15.f)));;
            GetShape(3)->setLocalPose(PxTransform(PxVec3(15.f,0.f,0.f)));
    
    
        }
            
    };
    //Distance joint with the springs switched on
    class DistanceJoint : public Joint
    {
    public:
        DistanceJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
        {
            PxRigidActor* px_actor0 = 0;
            if (actor0)
                px_actor0 = (PxRigidActor*)actor0->Get();
    
            joint = (PxJoint*)PxDistanceJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
            joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
            ((PxDistanceJoint*)joint)->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
            Damping(1.f);
            Stiffness(1.f);
        }
    
        void Stiffness(PxReal value)
        {
            ((PxDistanceJoint*)joint)->setStiffness(value);
        }
    
        PxReal Stiffness()
        {
            return ((PxDistanceJoint*)joint)->getStiffness();        
        }
    
        void Damping(PxReal value)
        {
            ((PxDistanceJoint*)joint)->setDamping(value);
        }
    
        PxReal Damping()
        {
            return ((PxDistanceJoint*)joint)->getDamping();
        }
    };
    
    ///Revolute Joint
    class RevoluteJoint : public Joint
    {
    public:
        RevoluteJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
        {
            PxRigidActor* px_actor0 = 0;
            if (actor0)
                px_actor0 = (PxRigidActor*)actor0->Get();
    
            joint = PxRevoluteJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
            joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
        }
    
        void DriveVelocity(PxReal value)
        {
            ((PxRevoluteJoint*)joint)->setDriveVelocity(value);
            ((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
        }
    
        PxReal DriveVelocity()
        {
            return ((PxRevoluteJoint*)joint)->getDriveVelocity();
        }
    
        void SetLimits(PxReal lower, PxReal upper)
        {
            ((PxRevoluteJoint*)joint)->setLimit(PxJointAngularLimitPair(lower, upper));
            ((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
        }
    };
}