#ifdef MINC2                    /* Ignore if not MINC2 */
/* minc_compat.c
 * 
 * this code exists to provide a dispatch layer between the MI2* low-level
 * calls and their respective HDF5 and NetCDF implementations.
 *
 * Since each of these calls uses exactly one file descriptor, the logic is 
 * simple: we just apply the correct operation based on a quick determination
 * of whether this is an HDF5 handle or a NetCDF file descriptor.
 */
#define _MI2_FORCE_NETCDF_
#include "netcdf.h"
#include "minc.h"
#include "minc_private.h"
#include "hdf_convenience.h"

/* */
int
MI2varname(int fd, int varid, char *varnm)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_varname(fd, varid, varnm));
    }
    else {
        return (nc_inq_varname(fd, varid, varnm));
    }
}

/* */
int
MI2varid(int fd, const char *varnm)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_varid(fd, varnm));
    }
    else {
        return (ncvarid(fd, varnm));
    }
}

/* */
int
MI2attinq(int fd, int varid, const char *attnm, nc_type *type_ptr,
          int *length_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_attinq(fd, varid, attnm, type_ptr, length_ptr));
    }
    else {
        int status;
        int oldncopts = ncopts;
        ncopts = 0;
        status = ncattinq(fd, varid, attnm, type_ptr, length_ptr);
        ncopts = oldncopts;
        if (status != 1 && oldncopts != 0) {
            fprintf(stderr,
                    _("ncattinq: ncid %d: varid: %d: Attribute '%s' not found"),
                    fd, varid, attnm);
	      
        }
        return (status);
    }
}

int
MI2attname(int fd, int varid, int attid, char *name)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_attname(fd, varid, attid, name));
    }
    else {
        return (ncattname(fd, varid, attid, name));
    }
}

/* */
int
MI2inquire(int fd, int *ndims_ptr, int *nvars_ptr, int *natts_ptr,
           int *unlimdim_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_inquire(fd, ndims_ptr, nvars_ptr, natts_ptr, unlimdim_ptr));
    }
    else {
        return (ncinquire(fd, ndims_ptr, nvars_ptr, natts_ptr, unlimdim_ptr));
    }
}

/* */
int
MI2varinq(int fd, int varid, char *varnm_ptr, nc_type *type_ptr,
          int *ndims_ptr, int *dims_ptr, int *natts_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_varinq(fd, varid, varnm_ptr, type_ptr, ndims_ptr, 
                           dims_ptr, natts_ptr));
    }
    else {
        return (ncvarinq(fd, varid, varnm_ptr, type_ptr, ndims_ptr, 
                         dims_ptr, natts_ptr));
    }
}

/* */
int
MI2dimid(int fd, const char *dimnm)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_dimid(fd, dimnm));
    }
    else {
        return (ncdimid(fd, dimnm));
    }
}

/* */
int
MI2diminq(int fd, int dimid, char *dimnm_ptr, long *len_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_diminq(fd, dimid, dimnm_ptr, len_ptr));
    }
    else {
        return (ncdiminq(fd, dimid, dimnm_ptr, len_ptr));
    }
}

/* */
int
MI2dimdef(int fd, const char *dimnm, long length)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_dimdef(fd, dimnm, length));
    }
    else {
        return (ncdimdef(fd, dimnm, length));
    }
}

/* */
int
MI2attget(int fd, int varid, const char *attnm, void *value)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_attget(fd, varid, attnm, value));
    }
    else {
        return (ncattget(fd, varid, attnm, value));
    }
}

/* */
int
MI2attput(int fd, int varid, const char *attnm, nc_type val_typ, 
          int val_len, void *val_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_attput(fd, varid, attnm, val_typ, val_len, val_ptr));
    }
    else {
        int old_ncopts = ncopts;
        int result;
        ncopts = 0;
        result = ncattput(fd, varid, attnm, val_typ, val_len, val_ptr);
        ncopts = old_ncopts;
        return (result);
    }
}

/* */
int
MI2endef(int fd)
{
    if (MI2_ISH5OBJ(fd)) {
        return (MI_NOERROR);    /* Just a stub, HDF5 doesn't do this! */
    }
    else {
        return (ncendef(fd));
    }
}  

/* */
int
MI2vardef(int fd, const char *varnm, nc_type vartype, int ndims,
          const int *dimids)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_vardef(fd, varnm, vartype, ndims, dimids));
    }
    else {
        return (ncvardef(fd, varnm, vartype, ndims, dimids));
    }
}

/* */
int
MI2varget(int fd, int varid, const long *start_ptr, 
          const long *count_ptr, void *val_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_varget(fd, varid, start_ptr, count_ptr, val_ptr));
    }
    else {
        return (ncvarget(fd, varid, start_ptr, count_ptr, val_ptr));
    }
}

/* */
int
MI2varput(int fd, int varid, const long *start_ptr,
          const long *count_ptr, const void *val_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_varput(fd, varid, start_ptr, count_ptr, val_ptr));
    }
    else {
        return (ncvarput(fd, varid, start_ptr, count_ptr, val_ptr));
    }
}

/* */
int
MI2varput1(int fd, int varid, const long *mindex_ptr,
           const void *val_ptr)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_varput1(fd, varid, mindex_ptr, val_ptr));
    }
    else {
        return (ncvarput1(fd, varid, mindex_ptr, val_ptr));
    }
}

int MI2attdel(int fd, int varid, const char *attnm)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_attdel(fd, varid, attnm));
    }
    else {
        return (ncattdel(fd, varid, attnm));
    }
}


/* */
int
MI2dimrename(int fd, int dimid, const char *new_name)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_dimrename(fd, dimid, new_name));
    }
    else {
        return (ncdimrename(fd, dimid, new_name));
    }
}

int
MI2varputg(int fd, int varid, const long *startp, const long *countp,
           const long *stridep, const long *imapp, const void *valp)
{
    if (MI2_ISH5OBJ(fd)) {
        return (hdf_varputg(fd, varid, startp, countp, stridep, imapp, valp));
    }
    else {
        return (ncvarputg(fd, varid, startp, countp, stridep, imapp, valp));
    }
}

int
MI2attcopy(int infd, int invarid, const char *name, int outfd, 
           int outvarid)
{
    if (!MI2_ISH5OBJ(infd) && !MI2_ISH5OBJ(outfd)) {
        /* Trivial case. */
        return (ncattcopy(infd, invarid, name, outfd, outvarid));
    }
    else {
        /* Complex case.  Using our own compatibility layer functions lets us
         * handle all three other possible combinations of infd & outfd types.
         */
        nc_type att_type;
        int att_length;
        void *val_ptr;
        int status;

        status = MI2attinq(infd, invarid, name, &att_type, &att_length);
        if (status == MI_ERROR) {
            return (MI_ERROR);
        }

        val_ptr = malloc(MI2typelen(att_type) * att_length);
        if (val_ptr == NULL) {
            return (MI_ERROR);
        }

        status = MI2attget(infd, invarid, name, val_ptr);
        if (status != MI_ERROR) {
            status = MI2attput(outfd, outvarid, name, att_type, att_length, val_ptr);
        }
    
        free(val_ptr);
        return (status);
    }
}

int
MI2typelen(int type_id)
{
    switch (type_id) {
    case NC_BYTE:
    case NC_CHAR:
        return (1);
    case NC_SHORT:
        return (2);
    case NC_INT:
    case NC_FLOAT:
        return (4);
    case NC_DOUBLE:
        return (8);
    default:
        break;
    }
    fprintf(stderr, _("Unknown type %d"), type_id);
    return (-1);
}

#endif /* MINC2 defined */
