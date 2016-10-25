#include "global_data_holder.h"
#include "SvgManager.h"
#include "analysis2d_cloth_static.h"
#include "designer2d_cloth.h"
GlobalDataHolder g_dataholder;

void GlobalDataHolder::init()
{
	// 2D patterns from svg
	m_svgManager.reset(new svg::SvgManager);

	// clothes related
	m_clothManger.reset(new CAnalysis2D_Cloth_Static);
	m_clothUiListener.reset(new CDesigner2D_Cloth);
	*m_param.m_clothParam = m_clothManger->GetParam_Cloth();
}

void GlobalDataHolder::generateClothDebug()
{
	m_clothUiListener->SetAnalysisInitialize(m_clothManger.get(), 6);
	m_clothManger->SetColor_FaceFEM(1.0, 1.0, 1.0);
	m_clothManger->SetTextureScale_FaceFEM(5);
	m_clothManger->SetIsLighting(true);
	m_clothUiListener->SetColor_CadFace(1, 1, 1);
	m_clothUiListener->SetTextureScale_CadFace(5);
	//m_clothUiListener->Solve_fromCad_InitValue();
	//m_clothManger->PerformStaticSolver();
	m_clothManger->SetClothPiecePlacingMode();
}

void GlobalDataHolder::svgToCloth()
{
	m_clothUiListener->ldp_disable_update = true;
	m_clothUiListener->SetAnalysisFromSvg(m_clothManger.get(), m_svgManager.get(), m_clothLoopId2svgIdMap);
	m_svgId2clothLoopIdMap.clear();
	for (auto it : m_clothLoopId2svgIdMap)
		m_svgId2clothLoopIdMap.insert(std::make_pair(it.second, it.first));
	m_clothManger->SetColor_FaceFEM(1.0, 1.0, 1.0);
	m_clothManger->SetTextureScale_FaceFEM(5);
	m_clothManger->SetIsLighting(true);
	m_clothUiListener->SetColor_CadFace(1, 1, 1);
	m_clothUiListener->SetTextureScale_CadFace(5);
	//m_clothUiListener->Solve_fromCad_InitValue();
	//m_clothManger->PerformStaticSolver();
	m_clothManger->SetClothPiecePlacingMode();
	m_clothUiListener->ldp_disable_update = false;
}