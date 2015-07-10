#pragma once

namespace dawn
{
  namespace CONSTANTS
  {
    enum Type {
      Object3D = 0,
      Camera,
      Scene,
      Mesh
    };

    enum CameraType {
      OrthographicCamera = 0,
      PerspectiveCamera
    };

    enum GeometryType {
      PlaneGeometry = 0,
      RoundedRectangleGeometry,
      BorderedRectangleGeometry,
      EllipsisGeometry,
      ArcGeometry,
      PolygonGeometry
    };

    enum MaterialType {
      ShaderMaterial = 0,
      FilterMaterial,
      VideoMaterial, // TODO Probably only need clear _or_ video material?
      ClearMaterial
    };

    enum FilterType
    {
      ShaderFilter = 0,
      GrayscaleFilter
    };

    enum PixelFormat {
      UnknownFormat = 0,

      AlphaFormat,

      RGBFormat,
      RGBAFormat,

      BGRFormat,
      BGRAFormat,

      LuminanceFormat
    };

    enum TextAlign {
        Left = 0,
        Center,
        Right
    };
  }
}
