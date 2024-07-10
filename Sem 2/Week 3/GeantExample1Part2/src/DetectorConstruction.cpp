#include "DetectorConstruction.h"
#include "EnergyCounter.h"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"
#include "G4GeometryManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorConstruction::m_magneticFieldMessenger = 0;

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

// Here we define the actual experiment that we want to perform
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Materials
  // http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html
  G4NistManager* nistManager = G4NistManager::Instance();
  G4Material* air = nistManager->FindOrBuildMaterial( "G4_AIR" );
  G4Material* lead = nistManager->FindOrBuildMaterial( "G4_Pb" );
  G4Material* aluminium = nistManager->FindOrBuildMaterial( "G4_Al" );

  // Sizes of the principal geometrical components (solids)
  G4double shieldThickness = 2.0*cm;
  G4double shieldRadius = 50.0*cm;
  G4double worldLength = 250.0*cm;

  // Definitions of Solids, Logical Volumes, Physical Volumes

  // WORLD: Solid (cube)
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent( worldLength );
  G4Box* worldS = new G4Box(
                 "World",         // its name
                 worldLength,
                 worldLength,
                 worldLength );   // its size (in half-lengths)

  // WORLD: Logical volume (how to treat it)
  G4LogicalVolume* worldLV = new G4LogicalVolume(
                 worldS,          // its solid
                 air,             // its material
                 "World" );       // its name

  // WORLD: Physical volume (where is it)
  // Must place the World Physical volume unrotated at (0,0,0).
  G4VPhysicalVolume* worldPV = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(0.0, 0.0, 0.0), // in the centre
                 worldLV,         // its logical volume
                 "World",         // its name
                 0,               // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                 true );          // checking overlaps


  // SHIELD: Solid (tube)
  G4Tubs* shieldS = new G4Tubs(
                 "Shield",        // its name
                 0.0,             // inner radius 0, so it's a solid cylinder (not a hollow tube)
                 shieldRadius,    // outer radius
                 shieldThickness, // how much material in the beam path (half length)
                 0.0*deg,         // starting angle
                 360.0*deg );     // ending angle (i.e. it's a full circle)

  // SHIELD: Logical volume (how to treat it)
  G4LogicalVolume* shieldLV = new G4LogicalVolume(
                 shieldS,         // its solid
                 lead,            // its material
                 "Shield",        // its name
                 0, 0, 0 );       // Modifiers we don't use

  // SHIELD: Physical volume (where is it)
  G4VPhysicalVolume* shieldPV = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(0.0, 0.0, 0.0), // in the centre
                 shieldLV,        // its logical volume
                 "Shield",        // its name
                 worldLV,         // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                 true );          // checking overlaps


  // BEHIND_SHEILD: Solid (cube)
  G4Box* cubeS = new G4Box(
                 "Behind_Shield",         // its name
                 40.0*cm,
                 40.0*cm,
                 40.0*cm );   // its size (in half-lengths)

  // BEHIND_SHEILD: Logical volume (how to treat it)
  G4LogicalVolume* cubeLV = new G4LogicalVolume(
                 cubeS,                   // its solid
                 aluminium,               // its material
                 "Behind_Shield" );       // its name

  // BEHIND_SHEILD: Physical volume (where is it)
  G4VPhysicalVolume* cubePV = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(0.0, 0.0, 42.0*cm), // in the centre
                 cubeLV,         // its logical volume
                 "Behind_Shield",         // its name
                 worldLV,               // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                 true );          // checking overlaps


  // SHIELD: Warn if there's an overlap
  if ( shieldPV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;

  // BEHIND_SHEILD: Warn if there's an overlap
  if ( cubePV->CheckOverlaps() ) std::cerr << "WARNING: your simulated objects overlap" << std::endl;

  // Always return the physical world
  return worldPV;
}

// Set up the magnetic field
void DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  m_magneticFieldMessenger = new G4GlobalMagFieldMessenger( fieldValue );

  // Register the field messenger for deleting
  G4AutoDelete::Register( m_magneticFieldMessenger );

  // Make "sensitive detectors"
  // objects that store information about incoming particles
  auto shieldDetector = new EnergyCounter( "Shield", 0 ); // Refers to histogram and ntuple ID 0
  G4SDManager::GetSDMpointer()->AddNewDetector( shieldDetector );
  this->SetSensitiveDetector( "Shield", shieldDetector );

  // Add cube to list
  auto cubeDetector = new EnergyCounter( "Behind_Shield", 1 ); // Refers to histogram and ntuple ID 1
  G4SDManager::GetSDMpointer()->AddNewDetector( cubeDetector );
  this->SetSensitiveDetector( "Behind_Shield", cubeDetector );
  
}
