<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">

  <xsl:param name="DeclarationUnit"></xsl:param>

  <xsl:output method="xml" indent="yes"/>
  <xsl:strip-space elements="*"/>

  <xsl:template match="/">
    <documentation>
      <xsl:apply-templates/>
    </documentation>
  </xsl:template>

  <xsl:template match="docs">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="members">
    <xsl:apply-templates select="./member[contains(@name,'T:')]"/>
  </xsl:template>

  <xsl:template match="member">
    <!-- We only care about members belong to the specified declaration unit. -->
    <xsl:if test="contains(@source,concat(lower-case($DeclarationUnit),'.h'))">

      <xsl:choose>
        <xsl:when test="contains(@name,'T:')">
          <xsl:variable name="MemberName" select="substring-after(@name,':')"/>
          <documented-type longname="{$MemberName}" shortname="{tokenize($MemberName,'\.')[last()]}">
            <!-- Select the member elements belonging to this type to nest them within
                 the fragment tree for this type. -->
            <xsl:apply-templates select="./remarks"/>
            <xsl:apply-templates select="//member[contains(@name,concat('M:',$MemberName,'.'))]"/>
            <xsl:apply-templates select="//member[contains(@name,concat('P:',$MemberName,'.'))]"/>
          </documented-type>
        </xsl:when>
        <xsl:when test="contains(@name,'M:') and contains(@name,'#ctor')">
          <documented-constructor>
            <xsl:variable name="ParameterTypes" select="tokenize(translate(substring-before(substring-after(@name,'('),')'),'@',''),',')"/>
            <xsl:for-each select="./param">
              <xsl:variable name="ParameterIndex" select="position()"/>
              <parameter longtype="{$ParameterTypes[$ParameterIndex]}" shorttype="{tokenize($ParameterTypes[$ParameterIndex],'\.')[last()]}" name="{@name}">
                <xsl:apply-templates select="."/>
              </parameter>
            </xsl:for-each>
            <xsl:apply-templates/>
          </documented-constructor>
        </xsl:when>
        <xsl:when test="contains(@name,'M:')">
          <documented-method name="{tokenize(substring-after(substring-before(@name,'('),':'),'\.')[last()]}">
            <xsl:variable name="ParameterTypes" select="tokenize(translate(substring-before(substring-after(@name,'('),')'),'@',''),',')"/>
            <xsl:for-each select="./param">
              <xsl:variable name="ParameterIndex" select="position()"/>
              <parameter longtype="{$ParameterTypes[$ParameterIndex]}" shorttype="{tokenize($ParameterTypes[$ParameterIndex],'\.')[last()]}" name="{@name}">
                <xsl:apply-templates select="."/>
              </parameter>
            </xsl:for-each>
            <xsl:apply-templates/>
          </documented-method>
        </xsl:when>
        <xsl:when test="contains(@name,'P:')">
          <documented-property name="{tokenize(substring-after(@name,':'),'\.')[last()]}">
            <xsl:apply-templates/>
          </documented-property>
        </xsl:when>
        <xsl:when test="contains(@name,'F:')">
          <documented-field name="{tokenize(substring-after(@name,':'),'\.')[last()]}">
            <xsl:apply-templates/>
          </documented-field>
        </xsl:when>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <xsl:template match="remarks | summary">
    <discussion>
      <xsl:apply-templates/>
    </discussion>
  </xsl:template>

  <xsl:template match="param">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="returns">
    <return-value>
      <xsl:apply-templates/>
    </return-value>
  </xsl:template>

  <xsl:template match="see">
    <pagelink target="{translate(substring-after(@cref,':'),'@','')}"/>
  </xsl:template>

  <xsl:template match="wiki">
    <pagelink target="{@page}"/>
  </xsl:template>

</xsl:transform>
