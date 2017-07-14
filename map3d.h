#ifndef MAP3D_H
#define MAP3D_H

#include <memory>
#include <QColor>
#include <QMatrix4x4>

#include "qgscoordinatetransform.h"

class QgsMapLayer;
class QgsRasterLayer;
class QgsVectorLayer;

class MapTextureGenerator;
class TerrainGenerator;

class PolygonRenderer
{
public:
  QgsVectorLayer* layer;  //!< layer used to extract polygons from
  float height;           //!< base height of polygons
  float extrusionHeight;  //!< how much to extrude (0 means no walls)
  QColor ambientColor;
  QColor diffuseColor;
};

class PointRenderer
{
public:
  QgsVectorLayer* layer;  //!< layer used to extract points from
  float height;
  QColor diffuseColor;
  QVariantMap shapeProperties;  //!< what kind of shape to use and what
  QMatrix4x4 transform;  //!< transform of individual instanced models
};

//! Definition of the world
class Map3D
{
public:
  Map3D();

  double originX, originY, originZ;   //!< coordinates in map CRS at which our 3D world has origin (0,0,0)
  QgsCoordinateReferenceSystem crs;   //!< destination coordinate system of the world  (TODO: not needed? can be
  double zExaggeration;

  QColor backgroundColor;   //!< background color of the scene

  QList<QgsMapLayer*> layers;   //!< layers to be rendered
  int tileTextureSize;   //!< size of map textures of tiles in pixels (width/height)

  std::unique_ptr<TerrainGenerator> terrainGenerator;

  QList<PolygonRenderer> polygonRenderers;   //!< stuff to render as polygons
  QList<PointRenderer> pointRenderers;   //!< stuff to render as points

  bool skybox;  //!< whether to render skybox
  QString skyboxFileBase;
  QString skyboxFileExtension;

  bool showBoundingBoxes;  //!< whether to show bounding boxes of entities - useful for debugging
  bool drawTerrainTileInfo;  //!< whether to draw extra information about terrain tiles to the textures - useful for debugging
};


#endif // MAP3D_H
