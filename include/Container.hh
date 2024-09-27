#ifndef Container_h
#define Container_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4UserLimits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
#include <iostream>
#include <stdlib.h>


// class G4VPhysicalVolume;
// class G4LogicalVolume;

class Container
{
  public:
     Container();
    ~Container();
    G4VPhysicalVolume* ConstructContainer(G4LogicalVolume* MotherVolume);

    G4double GetConMinXout()           {   return  conMinXout;        };
    G4double GetConMaxXout()           {   return  conMaxXout;        };
    G4double GetConMinYout()           {   return  conMinYout;        };
    G4double GetConMaxYout()           {   return  conMaxYout;        };
    G4double GetConMinZout()           {   return  conMinZout;        };
    G4double GetConMaxZout()           {   return  conMaxZout;        };

    G4double GetConMinXin()            {   return  conMinXin;         };
    G4double GetConMaxXin()            {   return  conMaxXin;         };
    G4double GetConMinYin()            {   return  conMinYin;         };
    G4double GetConMaxYin()            {   return  conMaxYin;         };
    G4double GetConMinZin()            {   return  conMinZin;         };
    G4double GetConMaxZin()            {   return  conMaxZin;         };

    G4double GetConXlengthout()        {   return  conXlengthout;     };
    G4double GetConYlengthout()        {   return  conYlengthout;     };
    G4double GetConZlengthout()        {   return  conZlengthout;     };

    G4double GetConXlengthin()         {   return  conXlengthin;      };
    G4double GetConYlengthin()         {   return  conYlengthin;      };
    G4double GetConZlengthin()         {   return  conZlengthin;      };

    G4double GetConCenterX()           {   return  conCenterX;        };
    G4double GetConCenterY()           {   return  conCenterY;        };
    G4double GetConCenterZ()           {   return  conCenterZ;        };

  private:
    G4double conMinXout;
    G4double conMaxXout;
    G4double conMinYout;
    G4double conMaxYout;
    G4double conMinZout;
    G4double conMaxZout;

    G4double conMinXin;
    G4double conMaxXin;
    G4double conMinYin;
    G4double conMaxYin;
    G4double conMinZin;
    G4double conMaxZin;

    G4double conXlengthout;
    G4double conYlengthout;
    G4double conZlengthout;

    G4double conXlengthin;
    G4double conYlengthin;
    G4double conZlengthin;

    G4double conCenterX;
    G4double conCenterY;
    G4double conCenterZ;
};
#endif
