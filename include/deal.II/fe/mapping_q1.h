// ---------------------------------------------------------------------
//
// Copyright (C) 2000 - 2015 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------

#ifndef dealii__mapping_q1_h
#define dealii__mapping_q1_h


#include <deal.II/base/derivative_form.h>
#include <deal.II/base/config.h>
#include <deal.II/base/table.h>
#include <deal.II/base/qprojector.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/dofs/dof_accessor.h>
#include <deal.II/fe/mapping_q_generic.h>

#include <cmath>

DEAL_II_NAMESPACE_OPEN

/*!@addtogroup mapping */
/*@{*/


/**
 * Mapping of the reference to cell to a general
 * quadrilateral/hexahedra by $d$-linear shape functions.
 *
 * The mapping implemented by this class maps the reference (unit) cell
 * to a general grid cell with
 * straight lines in $d$ dimensions. (Note, however, that in 3D the
 * <i>faces</i> of a general, trilinearly mapped cell may be curved, even if the
 * edges are not). This is the standard mapping used for polyhedral domains. It
 * is also the mapping used throughout deal.II for many functions that come in
 * two variants, one that allows to pass a mapping argument explicitly and one
 * that simply falls back to the MappingQ1 class declared here.
 *
 * The shape functions for this mapping are the same as for the finite element FE_Q
 * of order 1. Therefore, coupling these two yields an isoparametric element.
 *
 * @author Guido Kanschat, 2000, 2001; Ralf Hartmann, 2000, 2001, 2005, Wolfgang Bangerth, 2015
 */
template <int dim, int spacedim=dim>
class MappingQ1 : public MappingQGeneric<dim,spacedim>
{
public:
  /**
   * Default constructor.
   */
  MappingQ1 ();

  // for documentation, see the Mapping base class
  virtual
  Mapping<dim,spacedim> *clone () const;

  /**
   * @name Mapping points between reference and real cells
   * @{
   */

  // for documentation, see the Mapping base class
  virtual
  Point<dim>
  transform_real_to_unit_cell (const typename Triangulation<dim,spacedim>::cell_iterator &cell,
                               const Point<spacedim>                            &p) const;

  /**
   * @}
   */


  /**
   * @name Interface with FEValues
   * @{
   */

public:
  /**
   * Use the InternalData class of the base class without modification
   * and additions.
   */
  typedef typename MappingQGeneric<dim,spacedim>::InternalData InternalData;

  /**
   * @}
   */

protected:

  /**
   * Constructor. This constructor is for odd purposes: MappingQ is
   * derived from this class (for historical reasons) and it needs a
   * way to pass down the "true" polynomial degree of the mapping.
   */
  MappingQ1 (const unsigned int degree);

  /**
   * Computes the support points of the mapping. For @p MappingQ1 these are
   * the vertices, as obtained by calling Mapping::get_vertices().
   *
   * By default, that function just computes the locations of the vertices as
   * reported by the Triangulation. However, other classes may override this
   * function. In particular, the MappingQ1Eulerian class does exactly this by
   * not computing the support points from the geometry of the current cell but
   * instead evaluating an externally given displacement field in addition to
   * the geometry of the cell.
   */
  virtual
  void
  compute_mapping_support_points(const typename Triangulation<dim,spacedim>::cell_iterator &cell,
                                 std::vector<Point<spacedim> > &a) const;
};



/**
 * In order to avoid creation of static MappingQ1 objects at several places in
 * the library (in particular in backward compatibility functions), we define
 * a static MappingQ1 objects once and for all places where it is needed.
 */
template <int dim, int spacedim=dim>
struct StaticMappingQ1
{
  static MappingQ1<dim, spacedim> mapping;
};


/*@}*/


DEAL_II_NAMESPACE_CLOSE

#endif
