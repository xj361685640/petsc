
#ifndef lint
static char vcid[] = "$Id: gcreate.c,v 1.97 1996/08/12 03:42:04 bsmith Exp curfman $";
#endif

#include "sys.h"
#include "mat.h"       /*I "mat.h"  I*/

/*@C
   MatGetTypeFromOptions - Determines from the options database what matrix
   format the user has specified.

   Input Parameter:
.  comm - the MPI communicator
.  type - the type of matrix desired, for example MATSEQAIJ, MATMPIAIJ
.  pre - optional string to prepend to the name

   Output Parameters:
.  set - flag indicating whether user set matrix type option.

   Basic Options Database Keys:
   These options return MATSEQxxx or MATMPIxxx,
   depending on the communicator, comm.
$    -mat_aij      : AIJ type
$    -mat_baij     : block AIJ type
$    -mat_dense    : dense type
$    -mat_bdiag    : block diagonal type

   More Options Database Keys:
$    -mat_seqaij   : MATSEQAIJ
$    -mat_mpiaij   : MATMPIAIJ
$    -mat_seqbaij  : MATSEQBAIJ
$    -mat_mpibaij  : MATMPIBAIJ
$    -mat_seqbdiag : MATSEQBDAIG
$    -mat_mpibdiag : MATMPIBDIAG
$    -mat_mpirowbs : MATMPIROWBS
$    -mat_seqdense : MATSEQDENSE
$    -mat_mpidense : MATMPIDENSE

   Note:
   This routine is automatically called within MatCreate() and MatLoad().

.keywords: matrix, get, format, from, options

.seealso: MatCreate(), MatLoad()
@*/

int MatGetTypeFromOptions(MPI_Comm comm,char *pre,MatType *type,int *set)
{
  int  size,flg1,flg2,flg3,flg4,flg5,flg8,flg9,flg10,flg12,flg13,ierr,flg11,flg14,flg15;
  char p[64];

  PetscStrcpy(p,"-");
  if (pre) PetscStrcat(p,pre);

  MPI_Comm_size(comm,&size);
  ierr = OptionsHasName(PETSC_NULL,"-help",&flg1); CHKERRQ(ierr);
  if (flg1) {
    PetscPrintf(comm,"Matrix format options:\n");
    PetscPrintf(comm,"  %smat_aij, %smat_seqaij, %smat_mpiaij\n",p,p,p);
    PetscPrintf(comm,"  %smat_baij, %smat_seqbaij, %smat_mpibaij\n",p,p,p);
    PetscPrintf(comm,"  %smat_dense, %smat_seqdense, %smat_mpidense\n",p,p,p);
    PetscPrintf(comm,"  %smat_mpirowbs, %smat_bdiag, %smat_seqbdiag, %smat_mpibdiag\n",p,p,p,p); 
  }
  ierr = OptionsHasName(pre,"-mat_seqdense",&flg1); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_mpidense",&flg2); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_seqbdiag",&flg3); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_mpibdiag",&flg4); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_mpirowbs",&flg5); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_seqbaij",&flg11); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_mpibaij",&flg14); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_mpiaij",&flg8); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_seqaij",&flg9); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_aij",&flg10); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_bdiag",&flg12); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_dense",&flg13); CHKERRQ(ierr);
  ierr = OptionsHasName(pre,"-mat_baij",&flg15); CHKERRQ(ierr);
  if (flg1) {
    *type = MATSEQDENSE;
    *set = 1;
  }
  else if (flg2) {
    *type = MATMPIDENSE;
    *set = 1;
  }
  else if (flg3) {
    *type = MATSEQBDIAG;
    *set = 1;
  }
  else if (flg4) {
    *type = MATMPIBDIAG;
    *set = 1;
  }
  else if (flg5) {
    *type = MATMPIROWBS;
    *set = 1;
  }
  else if (flg8) {
    *type = MATMPIAIJ;
    *set = 1;
  }
  else if (flg9){
    *type = MATSEQAIJ;
    *set = 1;
  }
  else if (flg10) {
    if (size == 1) *type = MATSEQAIJ;
    else *type = MATMPIAIJ;
    *set = 1;
  }  
  else if (flg11) {
    *type = MATSEQBAIJ;
    *set = 1;
  }
  else if (flg12) {
    if (size == 1) *type = MATSEQBDIAG;
    else *type = MATMPIBDIAG;
    *set = 1;
  }  
  else if (flg13) {
    if (size == 1) *type = MATSEQDENSE;
    else *type = MATMPIDENSE;
    *set = 1;
  } 
  else if (flg14) {
    *type = MATMPIBAIJ;
    *set = 1;
  }  
  else if (flg15) {
    if (size == 1) *type = MATSEQBAIJ;
    else *type = MATMPIBAIJ;
    *set = 1;
  }  
  else {
    if (size == 1) *type = MATSEQAIJ;
    else *type = MATMPIAIJ;
    *set = 0;
  }
  return 0;
}

/*@C
   MatCreate - Creates a matrix where the type is determined
   from the options database. Generates a parallel MPI matrix if the
   communicator has more than one processor.  The default matrix type is
   AIJ, using the routines MatCreateSeqAIJ() and MatCreateMPIAIJ(). 

   Input Parameters:
.  m - number of global rows
.  n - number of global columns
.  comm - MPI communicator
 
   Output Parameter:
.  A - the matrix

   Basic Options Database Keys:
   These options use MatCreateSeqXXX or MatCreateMPIXXX,
   depending on the communicator, comm.
$    -mat_aij      : AIJ type
$    -mat_baij     : block AIJ type
$    -mat_dense    : dense type
$    -mat_bdiag    : block diagonal type

   More Options Database Keys:
$    -mat_seqaij   : AIJ type, uses MatCreateSeqAIJ()
$    -mat_mpiaij   : AIJ type, uses MatCreateMPIAIJ()
$    -mat_seqbdiag : block diagonal type, uses 
$                    MatCreateSeqBDiag()
$    -mat_mpibdiag : block diagonal type, uses 
$                    MatCreateMPIBDiag()
$    -mat_mpirowbs : rowbs type, uses MatCreateMPIRowbs()
$    -mat_seqdense : dense type, uses MatCreateSeqDense()
$    -mat_mpidense : dense type, uses MatCreateMPIDense()
$    -mat_seqbaij  : block AIJ type, uses MatCreateSeqBAIJ()
$    -mat_mpibaij  : block AIJ type, uses MatCreateMPIBAIJ()

   Even More Options Database Keys:
   See the manpages for particular formats (e.g., MatCreateSeqAIJ())
   for additional format-specific options.

   Notes:
   This routine calls MatGetTypeFromOptions() to determind the matrix type.

.keywords: matrix, create

.seealso: MatCreateSeqAIJ((), MatCreateMPIAIJ(), 
          MatCreateSeqBDiag(),MatCreateMPIBDiag(),
          MatCreateSeqDense(), MatCreateMPIDense(), 
          MatCreateMPIRowbs(), MatCreateSeqBAIJ,
          MatConvert(), MatGetTypeFromOptions()
 @*/
int MatCreate(MPI_Comm comm,int m,int n,Mat *A)
{
  MatType type;
  int     set, ierr, bs=1, flg;

  ierr = MatGetTypeFromOptions(comm,0,&type,&set); CHKERRQ(ierr);
  switch (type) {
  case MATSEQDENSE:
    ierr = MatCreateSeqDense(comm,m,n,PETSC_NULL,A); CHKERRQ(ierr);
    break;
  case MATMPIBDIAG:
    ierr = MatCreateMPIBDiag(comm,PETSC_DECIDE,m,n,PETSC_DEFAULT,PETSC_DEFAULT,
           PETSC_NULL,PETSC_NULL,A); CHKERRQ(ierr);
    break;
  case MATSEQBDIAG:
    ierr = MatCreateSeqBDiag(comm,m,n,PETSC_DEFAULT,PETSC_DEFAULT,PETSC_NULL,
           PETSC_NULL,A); CHKERRQ(ierr);
    break;
  case MATMPIROWBS:
    ierr = MatCreateMPIRowbs(comm,PETSC_DECIDE,m,PETSC_DEFAULT,PETSC_NULL,
           PETSC_NULL,A); CHKERRQ(ierr);
    break;
  case MATMPIDENSE:
    ierr = MatCreateMPIDense(comm,PETSC_DECIDE,PETSC_DECIDE,m,n,PETSC_NULL,A); CHKERRQ(ierr);
    break;
  case MATMPIAIJ:
    ierr = MatCreateMPIAIJ(comm,PETSC_DECIDE,PETSC_DECIDE,m,n,PETSC_DEFAULT,
           PETSC_NULL,PETSC_DEFAULT,PETSC_NULL,A); CHKERRQ(ierr);
    break;
  case MATSEQBAIJ:
    ierr = OptionsGetInt(PETSC_NULL,"-mat_block_size",&bs,&flg); CHKERRQ(ierr);
    ierr = MatCreateSeqBAIJ(comm,bs,m,n,PETSC_DEFAULT,PETSC_NULL,A); CHKERRQ(ierr);
    break;
  case MATMPIBAIJ:
    ierr = OptionsGetInt(PETSC_NULL,"-mat_block_size",&bs,&flg); CHKERRQ(ierr);
    ierr = MatCreateMPIBAIJ(comm,bs,PETSC_DECIDE,PETSC_DECIDE,m,n,PETSC_DEFAULT,PETSC_NULL,PETSC_DEFAULT,PETSC_NULL,A); CHKERRQ(ierr);
    break;
  default:
    ierr = MatCreateSeqAIJ(comm,m,n,PETSC_DEFAULT,PETSC_NULL,A); CHKERRQ(ierr);
    break;
  }
  return 0;
}

#include "src/mat/matimpl.h"
/*@C
   MatGetType - Gets the matrix type and name (as a string) from the matrix.

   Input Parameter:
.  mat - the matrix

   Output Parameter:
.  type - the matrix type (or use PETSC_NULL)
.  name - name of matrix type (or use PETSC_NULL)

.keywords: matrix, get, type, name
@*/
int MatGetType(Mat mat,MatType *type,char **name)
{
  int  itype = (int)mat->type;
  char *matname[10];

  if (type) *type = (MatType) mat->type;
  if (name) {
    /* Note:  Be sure that this list corresponds to the enum in mat.h */
    matname[0] = "MATSEQDENSE";
    matname[1] = "MATSEQAIJ";
    matname[2] = "MATMPIAIJ";
    matname[3] = "MATSHELL";
    matname[4] = "MATMPIROWBS";
    matname[5] = "MATSEQBDIAG";
    matname[6] = "MATMPIBDIAG";
    matname[7] = "MATMPIDENSE";
    matname[8] = "MATSEQBAIJ";
    matname[9] = "MATMPIBAIJ";
    
    if (itype < 0 || itype > 9) *name = "Unknown matrix type";
    else                        *name = matname[itype];
  }
  return 0;
}
 


