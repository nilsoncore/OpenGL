#ifndef GE_ENTITY_H_INCLUDED
#define GE_ENTITY_H_INCLUDED

struct eSEntityFlags
{
	GEU32 m_Locked : 1;  // 00000001 0
	GEU32 m_ProcessingDisabled : 1;  // 00000002 1
	GEU32 m_RenderingEnabled : 1;  // 00000004 2
	GEU32 m_Enabled : 1;  // 00000008 3
	GEU32 m_DeactivationEnabled : 1;  // 00000020 5
	GEU32 m_Killed : 1;  // 00000040 6
	GEU32 m_InProcessingRange : 1;  // 00000080 7
	GEU32 m_CachedIn : 1;  // 00000100 8
	GEU32 m_CachingInOut : 1;  // 00000200 9
	GEU32 m_Hook : 1;  // 00000400 10
	GEU32 m_Pickable : 1;  // 00000800 11
	GEU32 m_CollisionEnabled : 1;  // 00001000 12
	GEU32 m_InsertType : 4;  // 0003C000 14..17 // eCEntity::eEInsertType
	GEU32 m_LocalNodeBoundaryValid : 1;  // 00080000 19
	GEU32 m_WorldNodeBoundaryValid : 1;  // 00100000 20
	GEU32 m_WorldTreeBoundaryValid : 1;  // 00200000 21
	GEU32 Dynamic : 1;  // 00800000 23
	GEU32 m_SpecialDepthTexPassEnabled : 1;  // 02000000 25
	GEU32 m_Processable : 1;  // 04000000 26
	GEU32 m_ProcessingRangeOutFadingEnabled : 1;  // 10000000 28
	GEU32 m_Temporary : 1;  // 20000000 29
};

class eCFrustumElementItem;
enum eEInsertType;
class eCPhysicObject;
class eCEffector;
class eCEffectorDesc;
class eCJoint;
class eCJointDesc;
class eCEntityProxyInternal;

class GE_DLLIMPORT eCEntity : public eCNode
{
public:    virtual void                     SetName();
public:    virtual GEBool                   HasCreator(void) const;
public:    virtual GEBool                   IsAutoKillEnabled(void) const;
public:    virtual GEBool                   IsDummy(void) const;
public:    virtual GEBool                   IsKilled(void) const;
public:    virtual void                 GetLinearVelocity(void) const;
public:    virtual void                     Render(GEI16);
public:    virtual GEBool                   IsHelperParent(void) const;
protected: virtual bEResult                 ReadV83(bCIStream&, GEU16);
protected: virtual bEResult                 ReadV63(bCIStream&, GEU16);
protected: virtual void                     OnUpdatedWorldMatrix(void);
protected: virtual void                     OnUpdatedWorldTreeBoundary(void);
public:    virtual void                     UpdateLocalBoundary(void);
public:    virtual void                     UpdateParentDependencies(void);
public:    virtual void                     UpdateChildDependencies(void);
public:    virtual void                     Kill(void);
protected: virtual void                     OnCacheIn(void);
public:    virtual GEBool                   IsResource(void) const;
protected: virtual GEBool                   OnCreateFromTemplate(eCTemplateEntity const&);
protected: virtual GEBool                   OnPatchWithTemplate(eCTemplateEntity const&, GEBool, GEBool);
protected: virtual void                     SetCreator(eCTemplateEntity*);
public:    virtual eCTemplateEntity const* GetCreator(void) const;
public:    virtual GEBool                   IsResourceData(void) const;
protected: virtual void                     CopyEntityPrivateData(eCEntity const&, GEBool);
public:    virtual GEU32                    Modified(void);
protected: virtual void                     OnEnterProcessingRange(void);
protected: virtual void                     OnExitProcessingRange(void);
protected: virtual void                     OnUpdateInternals(void);
protected: virtual void                     OnCacheOut(void);
protected: virtual void                     OnDeinitialize(void);
protected: virtual void                     OnPostProcess(void);
protected: virtual void                     OnPreProcess(void);
protected: virtual void                     OnPostRead(void);
protected: virtual void                     OnProcess(void);;

protected: virtual void             OnChildrenAvailable(void);
public:    virtual void             RenderAlpha(GEI16);
public:    virtual GEU16            GetVersion(void) const;
public:    virtual bEResult         Write(bCOStream&);
public:    virtual bEResult         Read(bCIStream&);
public:    virtual void             Destroy(void);
public:    virtual bEResult         Create(void);
protected: virtual                 ~eCEntity(void);
public:    virtual eCEntity const* GetParent(void) const;
public:    virtual eCEntity* GetParent(void);
public:    virtual eCEntity const* GetRoot(void) const;
public:    virtual eCEntity const* GetChildAt(GEInt) const;
public:    virtual eCEntity* GetChildAt(GEInt);
public:    virtual void             Decay(void);
public:    virtual void             RemoveAllChildren(void);
public:    virtual void             ChildrenAvailable(GEBool);

protected:
	static GEBool ms_bDisableChildrenAvailableCall;
	static GEBool ms_bEntityPatchingEnabled;
	static GEBool ms_bForceEntityPatching;

public:
	static void GE_STDCALL   DisableChildrenAvailableCall(GEBool);
	static void GE_STDCALL   EnableEntityPatching(GEBool);
	static void GE_STDCALL   EnableForceEntityPatching(GEBool);
	static GEBool GE_STDCALL IsChildrenAvailableDisabled(void);
	static GEBool GE_STDCALL IsEntityPatchingEnabled(void);

public:
	void                         CacheIn(GEBool);
	void                         CacheOut(GEBool, GEBool);
	GEBool                       CanBeDeactivated(void) const;
	GEBool                       CanCollideWith(eCEntity*) const;
	eCEntity* CloneIntoWorld(void) const;
	GEBool                       CreateFromTemplate(eCTemplateEntity const&);
	void                         CreatePhysicObject(void);
	void                         Deinitialize(GEBool);
	void                         DestroyPhysicObject(void);
	void                         DisableProcessing(GEBool);
	void                         DoDelete(void);
	void                         Enable(GEBool);
	void                         EnableCollision(GEBool);
	void                         EnableCollisionWith(eCEntity*, GEBool);
	void                         EnableDeactivation(GEBool);
	void                         EnablePicking(GEBool, GEBool);
	void                         EnableRendering(GEBool);
	void                         EnableShapeCollision(eEShapeGroup, GEBool, GEInt);
	void                         EnableSpecialDepthTexPass(GEBool);
	
	void                         GetAziElev(eCEntity const&, GEFloat&, GEFloat&) const;
	eECollisionGroup             GetCollisionGroup(void) const;
	GEU32                        GetDataChangedTimeStamp(void) const;
	GEFloat                      GetDistanceToEntity2(eCEntity const&) const;
	GEFloat                      GetDistanceToEntity(eCEntity const&) const;
	GEFloat                      GetDistanceToEntityApprox(eCEntity const&) const;
	eSEntityFlags const& GetEntityFlags(void) const;
	eCFrustumElementItem& GetFrustumElementItem(void);
	eCFrustumElementItem const& GetFrustumElementItem(void) const;
	eEInsertType                 GetInsertType(void) const;
	GEU8                         GetLastRenderPriority(void) const;
	GEFloat                      GetObjectCullFactor(void) const;
	eCPhysicObject* GetPhysicObject(void);
	eCPhysicObject const* GetPhysicObject(void) const;
	GEU16& GetRefCountTAPoints(void);
	GEFloat                      GetRenderAlphaValue(void) const;
	GEFloat                      GetUniformScaling(void) const;
	GEFloat                      GetVisualLoDFactor(void) const;
	GEBool                       HasCollision(void) const;
	GEBool                       HasProcessingRangeEntered(void) const;
	GEBool                       HasPropertySet(eEPropertySetType) const;
	GEBool                       HasRenderAlphaComponent(void);
	GEBool                       HasVisual(void) const;
	GEBool                       IsCachedIn(void) const;
	GEBool                       IsCachingInOut(void) const;
	GEBool                       IsEnabled(void) const;
	GEBool                       IsFreeLOS(eCEntity*, GEBool) const;
	GEBool                       IsHook(void) const;
	GEBool                       IsInFOV(eCEntity*) const;
	GEBool                       IsLocked(void) const;
	GEBool                       IsPhysicRelevant(void) const;
	GEBool                       IsPickable(void) const;
	GEBool                       IsProcessable(void) const;
	GEBool                       IsProcessingDisabled(void) const;
	GEBool                       IsProcessingRangeOutFadingEnabled(void) const;
	GEBool                       IsRenderingEnabled(void) const;
	GEBool                       IsSpecialDepthTexPassEnabled(void) const;
	GEBool                       IsValidPropertySetIndex(GEInt) const;
	GEBool                       IsWaitingForPlayer_FollowNPC(void) const;
	eCEffector* LinkTo(eCEntity*, eCEffectorDesc&);
	eCJoint* LinkTo(eCEntity*, eCJointDesc&);
	void                         Lock(GEBool);
	void                         MoveToLocalNode(eCEntity*);
	void                         MoveToWorldNode(eCEntity*);
	GEBool                       PatchWithTemplate(eCTemplateEntity const&, GEBool);
	void                         PostProcess(GEBool);
	void                         PostRead(GEBool);
	void                         PreProcess(GEBool);
	void                         PrintDebug(void);
	void                         Process(GEBool);
	void                         RemoveAllPropertySets(void);
	void                         RemoveFromParent(GEBool);
	void                         RemoveLink(eCEffector&);
	void                         RemoveLink(eCJoint&);
	GEBool                       RemovePropertySetAt(GEInt);
	void                         RenderBoundingBox(GEU32, GEBool, GEBool);
	void                         RenderCoordinateAxes(GEFloat, GEBool, GEBool, GEBool);
	void                         RenderName(GEFloat);
	void                         RenderTranslationAxes(GEFloat, GEBool, GEBool, GEBool);
	void                         SetCollisionGroup(eECollisionGroup);
	void                         SetInsertType(eEInsertType);
	void                         SetLastRenderPriority(GEU8);
	void                         SetObjectCullFactor(GEFloat);
	void                         SetProcessingRangeOutFadingEnabled(GEBool);
	void                         SetRenderAlphaValue(GEFloat, GEBool);
	void                         SetShapeGroup(eEShapeGroup, eEShapeGroup);
	void                         SetTemporary(void);
	void                         SetVisualLoDFactor(GEFloat);
	void                         SetWaitingForPlayer_FollowNPC(GEBool);
	void                         UpdateGeometry(void);
	void                         UpdateInternals(GEBool);

protected:
	eCEntity(eCEntity const&);
	eCEntity(void);

protected:
	eCEntity const& operator = (eCEntity const&);

protected:
	void                    CacheInInternal(void);
	void                    CacheOutInternal(GEBool);
	void                    EnterProcessingRange(GEBool);
	void                    ExitProcessingRange(GEBool);
	void                    Invalidate(void);
	void                    KillIntern(void);
	eCEntityProxyInternal* QueryEntityProxyInternal(void);
	void                    ReleaseEntityProxyInternal(void);
	GEU16                   SearchForEntity(eEPropertySetType) const;
	void                    SetAsHook(GEBool);

private:
	void SetPhysicObject(eCPhysicObject*);

public:
	eCPhysicObject* m_pPhysicObject;
	GEFloat                             m_fRenderAlphaValue;
	GEChar                              m_u8LastRenderPriority;
	eSEntityFlags                       m_EntityFlags;
	GEFloat                             m_fVisualLoDFactor;
	GEFloat                             m_fObjectCullFactor;
	GEInt                               m_uDataChangedTimeStamp;
	GEFloat                             m_fUniformScaling;
	GEI16                               m_u16RefCountTAPoints;
	GEBool                              m_bWaitingForPlayer_FollowNPC;
};
#endif
