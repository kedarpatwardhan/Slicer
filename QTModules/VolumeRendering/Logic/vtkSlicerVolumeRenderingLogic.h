/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkSlicerVolumeRenderingLogic.h,v $
  Date:      $Date: 2006/01/08 04:48:05 $
  Version:   $Revision: 1.45 $

=========================================================================auto=*/

// .NAME vtkSlicerVolumeRenderingLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerVolumeRenderingLogic_h
#define __vtkSlicerVolumeRenderingLogic_h

// VolumeRendering includes
#include "vtkSlicerVolumeRenderingModuleLogicExport.h"
class vtkMRMLVolumeRenderingDisplayNode;
class vtkMRMLVolumeRenderingScenarioNode;

// Slicer includes
#include "vtkSlicerModuleLogic.h"

// MRML includes
//#include <vtkMRMLVolumeNode.h>
//#include <vtkMRMLVolumePropertyNode.h>
//#include <vtkMRMLAnnotationROINode.h>
//#include "vtkMRMLVolumeRenderingDisplayNode.h"
//#include "vtkMRMLVolumeRenderingScenarioNode.h"
class vtkMRMLAnnotationROINode;
class vtkMRMLLabelMapVolumeDisplayNode;
class vtkMRMLNode;
class vtkMRMLScalarVolumeDisplayNode;
class vtkMRMLScalarVolumeNode;
class vtkMRMLViewNode;
class vtkMRMLVolumeDisplayNode;
class vtkMRMLVolumeNode;
class vtkMRMLVolumePropertyNode;

// VTK includes
class vtkColorTransferFunction;
class vtkPiecewiseFunction;
class vtkVolumeProperty;

// STD includes
#include <vector>

class vtkStringArray;

/// \ingroup Slicer_QtModules_VolumeRendering
class VTK_SLICER_VOLUMERENDERING_MODULE_LOGIC_EXPORT vtkSlicerVolumeRenderingLogic :
  public vtkSlicerModuleLogic
{
public:
  
  static vtkSlicerVolumeRenderingLogic *New();
  vtkTypeRevisionMacro(vtkSlicerVolumeRenderingLogic,vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);

  void AddVolumeRenderingDisplayNode(vtkMRMLVolumeRenderingDisplayNode* node);
  void RemoveVolumeRenderingDisplayNode(vtkMRMLVolumeRenderingDisplayNode* node);
  void AddAllVolumeRenderingDisplayNodes();
  void RemoveAllVolumeRenderingDisplayNodes();

  void CopyDisplayToVolumeRenderingDisplayNode(
    vtkMRMLVolumeRenderingDisplayNode* node,
    vtkMRMLVolumeDisplayNode* displayNode = 0);
  // Applies the properties (window level, threshold and color function) of
  // the scalar display node to the volume rendering displaynode.
  // If scalarDisplayNode is 0, it uses the first display node.
  void CopyScalarDisplayToVolumeRenderingDisplayNode(
    vtkMRMLVolumeRenderingDisplayNode* volumeRenderingDisplayNode,
    vtkMRMLScalarVolumeDisplayNode* scalarDisplayNode = 0);

  /// Applies the properties (threshold ) of
  /// the labelmap display node to the volume rendering displaynode.
  /// If labelMapDisplayNode is 0, it uses the first displaynode.
  void CopyLabelMapDisplayToVolumeRenderingDisplayNode(
    vtkMRMLVolumeRenderingDisplayNode* volumeRenderingDisplayNode,
    vtkMRMLLabelMapVolumeDisplayNode* labelMapDisplayNode = 0);

  void SetThresholdToVolumeProp(
    double scalarRange[2], double threshold[2], vtkVolumeProperty* node);

  void SetWindowLevelToVolumeProp(
    double scalarRange[2], double windowLevel[2],
    vtkLookupTable* lut, vtkVolumeProperty* node);
  void SetLabelMapToVolumeProp(vtkLookupTable* lut, vtkVolumeProperty* node);

  // Description:
  // Create DisplayNode
  vtkMRMLVolumeRenderingDisplayNode* CreateVolumeRenderingDisplayNode();

  // Description:
  // Update DisplayNode from VolumeNode,
  // if needed create vtkMRMLVolumePropertyNode and vtkMRMLAnnotationROINode
  // and initialize them from VolumeNode
  void UpdateDisplayNodeFromVolumeNode(vtkMRMLVolumeRenderingDisplayNode *paramNode, 
                                          vtkMRMLVolumeNode *volumeNode, 
                                          vtkMRMLVolumePropertyNode **propNode,
                                          vtkMRMLAnnotationROINode **roiNode);
  void UpdateDisplayNodeFromVolumeNode(vtkMRMLVolumeRenderingDisplayNode *paramNode, 
                                          vtkMRMLVolumeNode *volumeNode)
    {
    vtkMRMLVolumePropertyNode *propNode = NULL;
    vtkMRMLAnnotationROINode            *roiNode = NULL;
    this->UpdateDisplayNodeFromVolumeNode(paramNode, volumeNode, &propNode, &roiNode);
    };

  // Description:
  // Create VolumeRenderingScenarioNode
  vtkMRMLVolumeRenderingScenarioNode* CreateScenarioNode();

  // Description:
  // Remove ViewNode from VolumeRenderingDisplayNode for a VolumeNode,
  void RemoveViewFromVolumeDisplayNodes(vtkMRMLVolumeNode *volumeNode, 
                                        vtkMRMLViewNode *viewNode);

  // Description:
  // Find volume rendering display node reference in the volume
  vtkMRMLVolumeRenderingDisplayNode* GetVolumeRenderingDisplayNodeByID(vtkMRMLVolumeNode *volumeNode, 
                                                                    char *displayNodeID);
  // Description:
  // Find volume rendering display node referencing the view node and volume node
  vtkMRMLVolumeRenderingDisplayNode* GetVolumeRenderingDisplayNodeForViewNode(
                                                        vtkMRMLVolumeNode *volumeNode, 
                                                        vtkMRMLViewNode *viewNode);
  // Description:
  // Find volume rendering display node referencing the view node in the scene
  vtkMRMLVolumeRenderingDisplayNode* GetVolumeRenderingDisplayNodeForViewNode(
                                                        vtkMRMLViewNode *viewNode);

  // Description:
  // Find first volume rendering display node
  vtkMRMLVolumeRenderingDisplayNode* GetFirstVolumeRenderingDisplayNode(vtkMRMLVolumeNode *volumeNode);

  // Description
  // Find the first volume rendering display node that uses the ROI
  vtkMRMLVolumeRenderingDisplayNode* GetFirstVolumeRenderingDisplayNodeByROINode(vtkMRMLAnnotationROINode* roiNode);

  void UpdateTranferFunctionRangeFromImage(vtkMRMLVolumeRenderingDisplayNode* vspNode);

  //void UpdateFgTranferFunctionRangeFromImage(vtkMRMLVolumeRenderingDisplayNode* vspNode);

  //void UpdateVolumePropertyFromImageData(vtkMRMLVolumeRenderingDisplayNode* vspNode);

  //void SetupFgVolumePropertyFromImageData(vtkMRMLVolumeRenderingDisplayNode* vspNode);

  void FitROIToVolume(vtkMRMLVolumeRenderingDisplayNode* vspNode);

  vtkMRMLVolumePropertyNode* AddVolumePropertyFromFile (const char* filename);

  vtkMRMLScene* GetPresetsScene();

  bool IsDifferentFunction(vtkPiecewiseFunction* function1,
                           vtkPiecewiseFunction* function2) const;
  bool IsDifferentFunction(vtkColorTransferFunction* function1,
                           vtkColorTransferFunction* function2) const;

protected:
  vtkSlicerVolumeRenderingLogic();
  virtual ~vtkSlicerVolumeRenderingLogic();

  virtual void SetMRMLSceneInternal(vtkMRMLScene* scene);
  // Register local MRML nodes
  virtual void RegisterNodes();

  void OnMRMLSceneNodeAddedEvent(vtkMRMLNode* node);
  void OnMRMLSceneNodeRemovedEvent(vtkMRMLNode* node);
  void OnMRMLNodeModified(vtkMRMLNode* node);

  // Update from 
  void UpdateVolumeRenderingDisplayNode(vtkMRMLVolumeRenderingDisplayNode* node);

  typedef std::vector<vtkMRMLNode*> DisplayNodesType;
  DisplayNodesType DisplayNodes;

  bool LoadPresets(vtkMRMLScene* scene);
  vtkMRMLScene* PresetsScene;
private:

  vtkSlicerVolumeRenderingLogic(const vtkSlicerVolumeRenderingLogic&); // Not implemented
  void operator=(const vtkSlicerVolumeRenderingLogic&);               // Not implemented
};

#endif

