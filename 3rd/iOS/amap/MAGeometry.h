/*
 *  MAGeometry.h
 *  MAMapKit
 *
 *  
 *  Copyright 2011 Autonavi Inc. All rights reserved.
 *
 */
#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

typedef struct {
    CLLocationDegrees latitudeDelta;
    CLLocationDegrees longitudeDelta;
} MACoordinateSpan;

typedef struct {
	CLLocationCoordinate2D center;
	MACoordinateSpan span;
} MACoordinateRegion;

typedef struct {
    double x;
    double y;
} MAMapPoint;

typedef struct {
    double width;
    double height;
} MAMapSize;

typedef struct {
    MAMapPoint origin;
    MAMapSize size;
} MAMapRect;
