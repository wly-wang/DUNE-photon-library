#include <iostream>

#include "TSystem.h"
#include "TGeoManager.h"

typedef struct {
  const char* volume;
  int color;
} drawopt;


void protodune_draw(bool nowires = true)
{
  gSystem->Load("libGeom");
  gSystem->Load("libGdml");

  std::vector<std::string> geoms;
  geoms.push_back("protodunehd_v2_refactored");
  //geoms.push_back("dunevd10kt_3view_v2_refactored_1x8x14ref_ReflAnode");
  
  TCanvas *c1 = new TCanvas("c1","",200,200,1000,1000);
  gStyle->SetCanvasPreferGL(kTRUE);


  // coloring options
  drawopt optdune[] = {
    //{"volCathode", kYellow},
    //{"volCathodeLayer", kRed},
    //{"volCathodePlate", kGreen},
    //{"volLateralExternal", kGreen},
    //{"volArapucaLat_0-0",kGreen},
    //{"volFieldShaper",kBlack},
    //{"volOpDetSensitive_0-0-0",kRed}, //fist value is the big module, second colum number, thrid row number. 
    //{"volOpDetSensitive_0-0-1",kRed},

    //{"volOpDetSensitive_0-0-2",kRed},
    //{"volOpDetSensitive_0-0-3",kRed},

    //{"volOpDetSensitive_0-1-0",kRed},
    //{"volOpDetSensitive_0-1-1",kRed},

    //{"volOpDetSensitive_2-0-0",kRed},
    //{"volOpDetSensitive_2-0-1",kRed},

    //{"volOpDetSensitive_2-1-0",kRed},
    //{"volOpDetSensitive_2-1-1",kRed},

    //{"volOpDetSensitive_2-7-0",kRed},
    //{"volOpDetSensitive_2-7-1",kRed},

    //{"volOpDetSensitive_1-0-0",kYellow},//double.
    //{"volOpDetSensitive_1-0-1",kYellow},
    //{"volOpDetSensitive_1-0-2",kYellow},
    //{"volOpDetSensitive_1-0-3",kYellow},

    //{"volOpDetSensitive_1-3-0",kYellow},//double.
    //{"volOpDetSensitive_1-4-0",kYellow},
    //{"volOpDetSensitive_1-5-0",kYellow},
    //{"volOpDetSensitive_1-7-0",kYellow},
    //{"volOpDetSensitive_1-9-0",kYellow},
    //{"volOpDetSensitive_3-1-0",kYellow},
    //{"volOpDetSensitive_3-3-0",kYellow},
    //{"volOpDetSensitive_3-6-0",kYellow},
    //{"volOpDetSensitive_3-8-0",kYellow},

    //{"volArapuca_3-0",kGreen},
    //{"volCryostat",kGreen},
    {"volTPCPlaneVInner", kGreen},
    {"volTPCActiveInner",kRed},
    {"volTPCActiveOuter",kBlue}
  };
  
 
  for(unsigned int i=0; i<geoms.size(); i++){
    std::cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;

    std::stringstream file;
    file << geoms[i];
    if( nowires ) file << "_nowires";
    file << ".gdml";

    std::cout << "Checking " << file.str() << "\n" << std::endl;

    TGeoManager::Import(file.str().c_str());

    // set colors
    TGeoVolume *vol;
    for (int i=0;; ++i) {
      if (optdune[i].volume==0) break;
      vol=gGeoManager->FindVolumeFast(optdune[i].volume);
      if(vol){
        vol->SetLineColor(optdune[i].color);
      }
    }

    gGeoManager->FindVolumeFast("volCryostat")->Draw("gl");
    //gGeoManager->FindVolumeFast("volExternalActive")->Draw("gl");


  }
}