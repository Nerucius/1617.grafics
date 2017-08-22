# Computer Graphics and Data Visualization
Universidad de Barcelona 2016-17

## Practica 1 - RayTracing

Investigating the basics of computer graphics algorithms. Starting with implementing
a phisically-based rendering model using calculations that try to simulate how
light bounces around in a scene. Raycasting is used extensively:
- Lambertian, Metallic and Transparent Materials
- Light scattering when hitting an object
- See-through materials for water and glass
- Super Sampling Antialiasing for smoother output
- Multi-core raytracing optimizations with OpenMP

[Intersecting a Ray with a Cube](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection)

## Practica 2 - OpenGL

Using QT and the **OpenGL libraries** to create a working demo of several
GPU-accelerated concepts:
- Materials and Gouraud / Phong shading
- UV Texture coordinates for mapping textures onto geometry
- Model and World space transformations
- Custom shader pipeline including:
  - Vertex Shader
  - Fragment Shader
- Working camera for rotating the view around the model


## Practica 3 - WebGL Globe

Visualizing a dataset onto a WebGL-powered website, transforming existing data
into a proper format for consumption. Visualizing the dataset onto a globe with
3 coordinates per data point: **Longitude, Latitude and Magnitude**

**Bases de Dades**
- [Earthquakes Data Program](https://earthquake.usgs.gov/earthquakes/feed/v1.0/csv.php)
- [Tsunami Historical Data](https://www.ngdc.noaa.gov/nndc/struts/results?bt_0=&st_0=&type_8=EXACT&query_8=None+Selected&op_14=eq&v_14=&st_1=&bt_2=&st_2=&bt_1=&bt_10=&st_10=&ge_9=&le_9=&bt_3=&st_3=&type_19=EXACT&query_19=None+Selected&op_17=eq&v_17=&bt_20=&st_20=&bt_13=&st_13=&bt_16=&st_16=&bt_6=&st_6=&ge_21=&le_21=&bt_11=&st_11=&ge_22=&le_22=&d=7&t=101650&s=70)
- [Disaster Datasets](https://catalog.data.gov/dataset?_groups_limit=0&groups=disasters)
- [Kaggle Datasets](https://www.kaggle.com/datasets)
- [Kaggle - Terror atacks](https://www.kaggle.com/abigaillarion/terrorist-attacks-in-united-states)
