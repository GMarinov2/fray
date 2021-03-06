/***************************************************************************
 *   Copyright (C) 2009-2018 by Veselin Georgiev, Slavomir Kaslev,         *
 *                              Deyan Hadzhiev et al                       *
 *   admin@raytracing-bg.net                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/**
 * @File triangle.cpp
 * @Brief Methods of the Triangle class
 */

#include "triangle.h"

inline double det(const Vector& a, const Vector& b, const Vector& c)
{
	return (a^b) * c;
}

bool Triangle::intersect(Ray ray, const Vector& A, const Vector& B, const Vector& C, double& minDist,
						 double& l2, double& l3)
{
	Vector AB = B - A;
	Vector AC = C - A;
	Vector D = -ray.dir;
	
	double Dcr = det(AB, AC, D);
	
	if (fabs(Dcr) < 1e-12) return false;
	double rDcr = 1 / Dcr;
	
	Vector H = ray.start - A;
	
	double gamma   = det(AB, AC, H) * rDcr;
	if (gamma < 0 || gamma > minDist) return false;

	double lambda2 = det(H, AC, D) * rDcr;
	if (lambda2 < 0 || lambda2 > 1) return false;
	
	double lambda3 = det(AB, H, D) * rDcr;
	
	if (lambda3 < 0 || lambda3 > 1) return false;
	
	double lambda1 = 1 - (lambda2 + lambda3);
	if (lambda1 < 0) return false;
	
	minDist = gamma;
	l2 = lambda2;
	l3 = lambda3;
	return true;
}

bool Triangle::intersectFast(Ray ray, const Vector& A, double& minDist, double& l2, double& l3) const
{
	Vector D = -ray.dir;
	
	double Dcr = dot(ABcrossAC, D);
	
	if (fabs(Dcr) < 1e-12) return false;
	double rDcr = 1 / Dcr;
	
	Vector H = ray.start - A;
	
	double gamma   = dot(ABcrossAC, H) * rDcr;
	if (gamma < 0 || gamma > minDist) return false;

	double lambda2 = det(H, AC, D) * rDcr;
	if (lambda2 < 0 || lambda2 > 1) return false;
	
	double lambda3 = det(AB, H, D) * rDcr;
	
	if (lambda3 < 0 || lambda3 > 1) return false;
	
	double lambda1 = 1 - (lambda2 + lambda3);
	if (lambda1 < 0) return false;
	
	minDist = gamma;
	l2 = lambda2;
	l3 = lambda3;
	return true;
}
