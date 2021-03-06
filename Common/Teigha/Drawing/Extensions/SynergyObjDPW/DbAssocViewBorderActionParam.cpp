/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2018, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Teigha(R) software pursuant to a license 
//   agreement with Open Design Alliance.
//   Teigha(R) Copyright (C) 2002-2018 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#include "OdaCommon.h"
#include "DbImpAssocViewBorderActionParam.h"
#include "DbFiler.h"
#include "DbAssocViewRepActionBody.h"
#include "ModelDocObj/DbViewBorder.h"

ODRX_DEFINE_MEMBERS_EX(OdDbAssocViewBorderActionParam,    // ClassName
                       OdDbAssocObjectActionParam,        // ParentClass
                       DBOBJECT_CONSTR,                   // DOCREATE
                       OdDb::kDHL_1027,                   // DwgVer
                       OdDb::kMRelease8,                  // MaintVer
                       1025,                              // nProxyFlags (kEraseAllowed | kDisableProxyWarning)
                       L"AcDbAssocViewBorderActionParam", // DWG class name
                       L"ACDBASSOCVIEWBORDERACTIONPARAM", // DxfName
                       L"AcSynergyObjDPW",                // AppName
                       OdRx::kMTLoading | OdRx::kHistoryAware);

OdDbAssocViewBorderActionParam::OdDbAssocViewBorderActionParam(bool createImpObj)
 : OdDbAssocObjectActionParam(false)
{
  if (createImpObj)
    m_pImpObj = new OdDbImpAssocViewBorderActionParam();
}

OdResult OdDbAssocViewBorderActionParam::dwgInFields(OdDbDwgFiler* pFiler)
{
  ODA_ASSERT_ONCE(m_pImpObj);
  if (!m_pImpObj)
    return eMakeMeProxy;

  OdResult res = OdDbObject::dwgInFields(pFiler);
  if (res != eOk)
    return res;
  return m_pImpObj->dwgInFields(pFiler, objectId());
}

void OdDbAssocViewBorderActionParam::dwgOutFields(OdDbDwgFiler* pFiler) const
{
  OdDbObject::dwgOutFields(pFiler);
  m_pImpObj->dwgOutFields(pFiler, objectId());
}

OdResult OdDbAssocViewBorderActionParam::dxfInFields(OdDbDxfFiler* pFiler)
{
  ODA_ASSERT_ONCE(m_pImpObj);
  if (!m_pImpObj)
    return eMakeMeProxy;

  OdResult res = OdDbObject::dxfInFields(pFiler);
  if (res != eOk)
    return res;

  return m_pImpObj->dxfInFields(pFiler, objectId());
}

void OdDbAssocViewBorderActionParam::dxfOutFields(OdDbDxfFiler* pFiler) const
{
  OdDbObject::dxfOutFields(pFiler);
  m_pImpObj->dxfOutFields(pFiler, objectId());
}


OdDbObjectId OdDbAssocViewBorderActionParam::viewBorderId() const
{
  assertReadEnabled();
  return ((OdDbImpAssocViewBorderActionParam*)m_pImpObj)->dependentOnObjectId();
}

OdDbObjectId OdDbAssocViewBorderActionParam::viewportId() const
{
  OdDbObjectId idRes;
  OdDbViewBorderPtr pViewBorder = OdDbViewBorder::cast(viewBorderId().openObject());
  if (!pViewBorder.isNull())
  {
    idRes = pViewBorder->viewportId();
  }
  return idRes;
}

