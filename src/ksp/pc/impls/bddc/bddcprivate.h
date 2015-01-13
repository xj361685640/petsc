/* prototypes of all BDDC private functions */
#if !defined(__pcbddc_private_h)
#define __pcbddc_private_h

#include <../src/ksp/pc/impls/bddc/bddcstructs.h>

/* main functions */
PetscErrorCode PCBDDCAnalyzeInterface(PC);
PetscErrorCode PCBDDCConstraintsSetUp(PC);

/* reset functions */
PetscErrorCode PCBDDCResetTopography(PC);
PetscErrorCode PCBDDCResetSolvers(PC);
PetscErrorCode PCBDDCResetCustomization(PC);

/* graph */
PETSC_EXTERN PetscErrorCode PCBDDCGraphCreate(PCBDDCGraph*);
PETSC_EXTERN PetscErrorCode PCBDDCGraphDestroy(PCBDDCGraph*);
PETSC_EXTERN PetscErrorCode PCBDDCGraphInit(PCBDDCGraph,ISLocalToGlobalMapping);
PETSC_EXTERN PetscErrorCode PCBDDCGraphReset(PCBDDCGraph);
PETSC_EXTERN PetscErrorCode PCBDDCGraphResetCSR(PCBDDCGraph);
PETSC_EXTERN PetscErrorCode PCBDDCGraphSetUp(PCBDDCGraph,PetscInt,IS,IS,PetscInt,IS[],IS);
PETSC_EXTERN PetscErrorCode PCBDDCGraphComputeConnectedComponents(PCBDDCGraph);
PETSC_EXTERN PetscErrorCode PCBDDCGraphComputeConnectedComponentsLocal(PCBDDCGraph);
PETSC_EXTERN PetscErrorCode PCBDDCGraphASCIIView(PCBDDCGraph,PetscInt,PetscViewer);
PETSC_EXTERN PetscErrorCode PCBDDCGraphGetCandidatesIS(PCBDDCGraph,PetscInt*,IS*[],PetscInt*,IS*[],IS*);

/* interface for scaling operator */
PetscErrorCode PCBDDCScalingSetUp(PC);
PetscErrorCode PCBDDCScalingDestroy(PC);
PetscErrorCode PCBDDCScalingRestriction(PC,Vec,Vec);
PetscErrorCode PCBDDCScalingExtension(PC,Vec,Vec);

/* nullspace stuffs */
PetscErrorCode PCBDDCNullSpaceAssembleCorrection(PC,IS);
PetscErrorCode PCBDDCNullSpaceAdaptGlobal(PC);
PetscErrorCode PCBDDCNullSpaceAssembleCoarse(PC,Mat,MatNullSpace*);

/* utils */
PetscErrorCode PCBDDCComputeLocalMatrix(PC,Mat);
PetscErrorCode PCBDDCSetUpLocalWorkVectors(PC);
PetscErrorCode PCBDDCSetUpSolvers(PC);
PetscErrorCode PCBDDCSetUpLocalScatters(PC);
PetscErrorCode PCBDDCSetUpLocalSolvers(PC,PetscBool,PetscBool);
PetscErrorCode PCBDDCSetUpCorrection(PC,PetscScalar**);
PetscErrorCode PCBDDCSetUpCoarseSolver(PC,PetscScalar*);
PetscErrorCode PCBDDCSubsetNumbering(MPI_Comm,ISLocalToGlobalMapping,PetscInt,PetscInt[],PetscInt[],PetscInt*,PetscInt*[]);
PetscErrorCode PCBDDCComputePrimalNumbering(PC,PetscInt*,PetscInt**);
PetscErrorCode PCBDDCGetPrimalVerticesLocalIdx(PC,PetscInt*,PetscInt**);
PetscErrorCode PCBDDCGetPrimalConstraintsLocalIdx(PC,PetscInt*,PetscInt**);
PetscErrorCode PCBDDCScatterCoarseDataBegin(PC,InsertMode,ScatterMode);
PetscErrorCode PCBDDCScatterCoarseDataEnd(PC,InsertMode,ScatterMode);
PetscErrorCode PCBDDCApplyInterfacePreconditioner(PC,PetscBool);
PetscErrorCode PCBDDCOrthonormalizeVecs(PetscInt,Vec[]);
PetscErrorCode PCBDDCSetUseExactDirichlet(PC,PetscBool);
PetscErrorCode PCBDDCSetLevel(PC,PetscInt);
PetscErrorCode PCBDDCGlobalToLocal(VecScatter,Vec,Vec,IS,IS*);

/* feti-dp */
PetscErrorCode PCBDDCCreateFETIDPMatContext(PC,FETIDPMat_ctx*);
PetscErrorCode PCBDDCSetupFETIDPMatContext(FETIDPMat_ctx);
PetscErrorCode PCBDDCCreateFETIDPPCContext(PC,FETIDPPC_ctx*);
PetscErrorCode PCBDDCSetupFETIDPPCContext(Mat,FETIDPPC_ctx);
PetscErrorCode FETIDPPCApply(PC,Vec,Vec);
PetscErrorCode PCBDDCDestroyFETIDPPC(PC);
PetscErrorCode FETIDPMatMult(Mat,Vec,Vec);
PetscErrorCode PCBDDCDestroyFETIDPMat(Mat);

/* sub schurs */
PetscErrorCode PCBDDCSubSchursCreate(PCBDDCSubSchurs*);
PetscErrorCode PCBDDCSubSchursInit(PCBDDCSubSchurs,Mat,Mat,IS,IS,PCBDDCGraph,PetscInt);
PetscErrorCode PCBDDCSubSchursDestroy(PCBDDCSubSchurs*);
PetscErrorCode PCBDDCSubSchursReset(PCBDDCSubSchurs);
PetscErrorCode PCBDDCSubSchursSetUpNew(PCBDDCSubSchurs,PetscInt[],PetscInt[],PetscInt);
PetscErrorCode PCBDDCSubSchursSetUp(PCBDDCSubSchurs,Mat,IS,IS,PetscInt,IS[],PetscInt[],PetscInt[],PetscInt);

#endif

